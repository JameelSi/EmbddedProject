#ifndef USART1TERMINAL_H_
#define USART1TERMINAL_H_




/******************************************************************************
Definitions
******************************************************************************/
//  Maximum allowed size of a command
#define SIZE_OF_COMMAND_BUFFER 128

/******************************************************************************
USART1TERMINAL_handleCommand
Description: Fetches a command from the USART1 RX buffer and executes it.
Note:
  The function assumes there is a command in the buffer.
******************************************************************************/
void USART1TERMINAL_handleCommand();



#endif /* USART1TERMINAL_H_ */
