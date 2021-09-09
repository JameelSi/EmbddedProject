#ifndef EVENTQ_H_
#define EVENTQ_H_
#include <stdio.h>
#include "types.h"
// chose buffer size of 128 for the whole program(big enough to handle the commands)
#define BUFFER_SIZE 128

/******************************************************************************
eventQ
	A cyclic buffer used to handle the events in order reached. This is made to
	Solve the problem where commands might be skipped when the system is busy
	Handling another task
******************************************************************************/

/******************************************************************************
Definitions
******************************************************************************/
/******************************************************************************
EVENT
	The program has three tasks to deal with: when button is pressed,when USART2
	Has a message and when USART1 has a message.
******************************************************************************/
typedef enum{
	EVENT_USART2_MESSAGE,
	EVENT_BUTTON_PRESSED,
	EVENT_USART1_MESSAGE
}EVENT;

/******************************************************************************
eventQ_init
Description: initialize the cyclic buffer.
******************************************************************************/
 void eventQ_init(void);

 /******************************************************************************
 eventQ_init
 Description: write to the queue the event
 ******************************************************************************/
 void eventQ_write(uint32_t q);

 /******************************************************************************
 eventQ_read
 Description: read from the queue(pull the event) and return it to be handled
 ******************************************************************************/
 uint32_t eventQ_read(void);
 /******************************************************************************
 eventQ_isEmpty
 Description: checks if the queue is empty or not
 ******************************************************************************/
 BOOL eventQ_isEmpty(void);

#endif /* EVENTQ_H_ */
