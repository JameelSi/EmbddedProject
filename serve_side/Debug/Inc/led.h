#ifndef LED_H_
#define LED_H_

/******************************************************************************
LED
  Handles everything related to led.Such as initializing it,turning it on or off
  This includes blinking the LED, after a command to do so is received,
  It uses Timer 2 to measure time intervals.
******************************************************************************/

/******************************************************************************
Definitions:
******************************************************************************/
#define BLINK_HALF_PERIOD_IN_SEC 1
// keep track of the led state so that we can change it to the next state when button is clicked
typedef enum{
	LED_STATE_ON,
	LED_STATE_OFF,
	LED_STATE_BLINK
}LED_STATE;


/******************************************************************************
LED_init
Description: Initializes the LED GPIO (PA5) and its interrupt.
******************************************************************************/
void LED_init(void);

/******************************************************************************
LED_off
Description: Turns the LED off.
******************************************************************************/
void LED_off(void);

/******************************************************************************
LED_off
Description: Turns the LED on.
******************************************************************************/
void LED_on(void);

/******************************************************************************
LED_off
Description: Toggles the LED.
******************************************************************************/
void LED_toggle(void);


/******************************************************************************
LED_handle
Description:
  Handle the expiration of Timer 2 (once a second).
  Execute timed tasks if relevant.
******************************************************************************/
void LED_blink_handle(void);

/******************************************************************************
LED_change_state
Description: a function that changes the led to the next state when triggered.
******************************************************************************/
void LED_change_state(void);

#endif /* LED_H_ */
