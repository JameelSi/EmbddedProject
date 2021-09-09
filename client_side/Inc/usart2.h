#ifndef USART2_H_
#define USART2_H_




/******************************************************************************
Includes
******************************************************************************/
#include "types.h"




/******************************************************************************
Definitions
******************************************************************************/
#define USART2_SIZE_OF_RX_BUFFER 128
#define USART2_SIZE_OF_PRINT_BUFFER 128




/******************************************************************************
print
Description: Functions as the stdio printf function.
Note:
  This function uses a buffer, whose size is determined by USART2_SIZE_OF_
  PRINT_BUFFER. Therefore, it is not reentrant.
******************************************************************************/
void print(char *p_format, ...);

/******************************************************************************
USART2_getCommand
Description:
  Copies the current command in the USART2 RX buffer.
  The '\n' at the end of the recieved command is replaced with a '\0'.
Input:
  p_command: Address to which to the command should be copied.
******************************************************************************/
void USART2_getCommand(char *p_command);

/******************************************************************************
USART2_init
Description: Initializes USART2 on GPIOs PA2 and PA3,
  with a baud rate of 9600.
******************************************************************************/
void USART2_init(void);

/******************************************************************************
USART2_print
Description: Prints a '\0'-terminated sequence of characters.
Input:
  p_data: The sequence to print.
******************************************************************************/
void USART2_print(const char *p_data);


#endif /* USART2_H_ */
