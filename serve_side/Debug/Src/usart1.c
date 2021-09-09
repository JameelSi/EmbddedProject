#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "stm32f303xe.h"
#include "types.h"
#include "usart1.h"
#include "usart2.h"
#include "cyclic_buffer.h"
#include "eventQ.h"


// This buffer is used to receive and write commands.
static cyclic_buffer usart1_cy;

void USART1_init(void){
	//Initialize the cyclic buffer used for usart1
	buffer_init(&usart1_cy);
    // Enable GPIOA clock (p. 148 in the datasheet).
    RCC->AHBENR |= 0x00020000;
    // Enable USART1 clock.
    RCC->APB2ENR |= 0x00004000;
    // Configure GPIOA pins 9tx and 10rx as alternate function 7, which is USART1.
    GPIOA->MODER |= 0x00280000;
    // and AFR[1] is the same as AFRH in the reference manual (p. 242).
    GPIOA->AFR[1] |= 0x00000770;
    // 8 MHz / set baud rate to 115200.
    USART1->BRR = 8000000/115200;
    // Enable USART1 and its RX and TX functionality.
    USART1->CR1 = 0x0000002D;
    //enable the RX interrupt.
    NVIC_EnableIRQ(USART1_IRQn);
}



void USART1_getCommand(char *p_command){
	// while the buffer isnt empty keep reading the next charachter from the buffer to the p_command
	char *temp=p_command;
	while(!buffer_isEmpty(&usart1_cy)){
		*temp=buffer_read(&usart1_cy);
		temp++;
	}
		*temp='\0';

}




void USART1_EXTI25_IRQHandler(void){

	char rx_byte;

	// Read the received byte into the cyclic buffer.
	// This also clears the interrupt request flag.
    rx_byte = USART1->RDR;
    // If the user entered '\n', a whole command has been received.
    if(rx_byte == '\n'){
    	// write to the queue that USART1 has a received command
    	eventQ_write(EVENT_USART1_MESSAGE);
    	// close the command with /n
    	buffer_write(&usart1_cy, '\n');

    	return;
    }
    buffer_write(&usart1_cy, rx_byte);
}


void USART1_print(const char *p_data){
	while(*p_data != '\0'){
		USART1->TDR = *p_data;
        p_data++;
        while(!(USART1->ISR & 0x00000080));
	}
}
