#include "led.h"
#include "stm32f303xe.h"
#include "types.h"
#include "usart2.h"

// initial state of the led is it to be off
static int currentState=LED_STATE_OFF;
static BOOL Blink = FALSE;
static unsigned char Blink_Counter = 0;

void LED_init(void){
    // Enable the GPIOA clock.
    RCC->AHBENR |= 0x00020000;
    // Configure PA5 as output
    // (by default it will then be push pull, see p. 237 of the reference manual).
    GPIOA->MODER |= 0x00000400;
}

void LED_off(void){
	GPIOA->ODR &= ~0x00000020;
}

void LED_on(void){
    GPIOA->ODR |= 0x00000020;
}

void LED_toggle(void){
	GPIOA->ODR ^= 0x00000020;
}

void LED_blink_handle(void){
	if(Blink){
        Blink_Counter++;
        if(Blink_Counter == BLINK_HALF_PERIOD_IN_SEC){
        	Blink_Counter = 0;
        	LED_toggle();
        }
	}
}
void LED_change_state(){
	switch( currentState ){
		// if led is off turn it on
		case LED_STATE_OFF:
			Blink = FALSE;
	    	LED_on();
	    	currentState=LED_STATE_ON;
			print("Server led is now on\n");
			break;
		// if led is on make it blink
		case LED_STATE_ON:
			Blink = TRUE;
			currentState=LED_STATE_BLINK;
			print("Server led is now blinking\n");
			break;
		// if led is blinking turn it off
		case LED_STATE_BLINK:
			Blink = FALSE;
			LED_off();
			currentState=LED_STATE_OFF;
			print("Server led is now off\n");
			break;
		default:
			break;
	}
}
