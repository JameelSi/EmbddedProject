#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "stm32f303xe.h"
#include "types.h"
#include "usart2.h"
#include "cyclic_buffer.h"
#include "eventQ.h"



// This cyclic buffer is used to receive and write commands.
static cyclic_buffer usart2_cy;
// This buffer is used by the printf-like print function.
static char A_Tx_Buffer[USART2_SIZE_OF_PRINT_BUFFER];

void USART2_init(void){
	// initialize USART2 cyclic buffer
	buffer_init(&usart2_cy);
    // Enable GPIOA clock (p. 148 in the datasheet).
    RCC->AHBENR |= 0x00020000;
    // Enable USART2 clock.
    RCC->APB1ENR |= 0x00020000;
    // Configure GPIOA pins 2 and 3 as alternate function 7, which is USART2.
    GPIOA->MODER |= 0x000000A0;
    // AFR[0] is the same as AFRL in the reference manual (p. 241),
    // and AFR[1] is the same as AFRH in the reference manual (p. 242).
    GPIOA->AFR[0] |= 0x00007700;
    USART2->BRR = 833;  // 8 MHz / 9600 baud rate.
    // Enable USART2 and its RX and TX functionality.
    // Also enable the RX interrupt.
    USART2->CR1 = 0x0000002D;
    NVIC_EnableIRQ(USART2_IRQn);
}

void print(char *p_format, ...){
	va_list p_variables;
	va_start(p_variables, p_format);
	(void)vsprintf(A_Tx_Buffer, p_format, p_variables);
    USART2_print(A_Tx_Buffer);
}






void USART2_getCommand(char *p_command){
		//while cyclic buffer isnt empty keep reading to it char by char to the p_command
		char *temp=p_command;
		while(!buffer_isEmpty(&usart2_cy)){
			*temp=buffer_read(&usart2_cy);
			temp++;
		}
		// close the command with \0
		*temp='\0';
}





void USART2_EXTI26_IRQHandler(void){
	char rx_byte;

	// Read the received byte into the buffer.
	// This also clears the interrupt request flag.
    rx_byte = USART2->RDR;

    // If the user entered '\n', a whole command has been received.
    if(rx_byte == '\n'){
    	// write to the queque that USART2 has a command/ message
    	eventQ_write(EVENT_USART2_MESSAGE);
    	buffer_write(&usart2_cy, '\0');
    	return;
    }

    buffer_write(&usart2_cy, rx_byte);
}




void USART2_print(const char *p_data){

	while(*p_data != '\0'){
		USART2->TDR = *p_data;
        p_data++;
        while(!(USART2->ISR & 0x00000080));
	}
}
