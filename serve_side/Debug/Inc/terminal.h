#ifndef TERMINAL_H_
#define TERMINAL_H_




/******************************************************************************
Definitions
******************************************************************************/
//  Maximum allowed size of a command (including the terminating '\n').
#define TERMINAL_SIZE_OF_COMMAND_BUFFER 128

/******************************************************************************
TERMINAL_handleCommand
Description: Fetches a command from the USART2 RX buffer and executes it.
Note:
  The function assumes there is a command in the buffer.
******************************************************************************/
void TERMINAL_handleCommand(void);



#endif /* TERMINAL_H_ */
