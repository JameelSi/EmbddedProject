/*****************************************************************************/
/* stm32 cards communication (Server side) by: Jameel S., Amani N.			 */
/* All references to the reference manual are to STM's RM0316, revision 8    */
/*****************************************************************************/
#include <string.h>
#include "stm32f303xe.h"
#include "eventQ.h"
#include "led.h"
#include "modem.h"
#include "terminal.h"
#include "timer2.h"
#include "usart1.h"
#include "usart2.h"
#include "types.h"
#include "usart1terminal.h"
#include "watchdog.h"
#include "button.h"
#include "cyclic_buffer.h"

int main(void){
	// initialize everything related for the program to work as its supposed to
    BUTTON_init();
    LED_init();
    TIMER2_init();
    USART1_init();
    USART2_init();
    eventQ_init();
    MODEM_init();
    WATCHDOG_init();
    print("I'm the server side, nice to meet you! \n");
    print("Use WIFICONNECT command to connect to wifi\n\n");


    while(1){
    	//keep checking for new events and handle them accordingly
    	if(!eventQ_isEmpty()){
    		uint32_t q=eventQ_read();
    		if(q==EVENT_BUTTON_PRESSED){
    			USART2_print("Button pressed!\n");
    			if(getClientState())
    				BUTTON_sendCommand();
    			else
    				USART2_print("but client isn't connected\r\n");
    		}
    		else if(q==EVENT_USART1_MESSAGE){
    			USART1TERMINAL_handleCommand();
    		}
    		else if(q==EVENT_USART2_MESSAGE){
            	TERMINAL_handleCommand();
    		}
			WATCHDOG_pet();

    	}
		 if(TIMER2_expired()){
			LED_blink_handle();
		}
		 WATCHDOG_pet();

    }
}
