#ifndef BUTTON_H_
#define BUTTON_H_




/******************************************************************************
Includes
******************************************************************************/
#include "types.h"




/******************************************************************************
BUTTON_init
Description: Initializes the button GPIO (PC13) and its interrupt.
******************************************************************************/
void BUTTON_init(void);

/******************************************************************************
BUTTON_sendCommand
Description:
	When triggered this function sends the command CHANGE_LED to the client
	Which changes the led for it.
******************************************************************************/
void BUTTON_sendCommand(void);

#endif /* BUTTON_H_ */
