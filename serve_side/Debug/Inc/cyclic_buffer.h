#ifndef CYCLIC_BUFFER_H_
#define CYCLIC_BUFFER_H_
// the size of the cyclic buffer (big enough not to make problems under pressure)
#define BUFFER_SIZE 128

/******************************************************************************
Includes
******************************************************************************/
#include "types.h"

/******************************************************************************
cyclic_buffer
	A buffer used to be written strings on and read from it's found to solve the
	Effectiveness and the "work under pressure" it's cyclic because when it reaches
	The end of the buffer it goes back to the beginning of it so we can say its endless.
	It uses an array of chars and two pointers (read,write) where both initially points
	At the beginning of the array and when a string is being written to it the write
	Pointer writes it char by char to the buffer while the read reads it also char
	By char, We know its empty when the write and read pointers are pointing to the
	Same spot.
******************************************************************************/

/******************************************************************************
Definitions
******************************************************************************/
typedef struct {
	char buffer[BUFFER_SIZE];
	char *write;
	char *read;
} cyclic_buffer;

/******************************************************************************
buffer_init
Description: initialize the buffer.
(makes the read,write pointers point to the beginning of the buffer)
******************************************************************************/
 void buffer_init(cyclic_buffer *cy);

 /******************************************************************************
 buffer_write
 Description:
 	 The function receives a cyclic buffer to write to and a char to be written
 	 And writes the char at the position the write pointer currently is pointing
 	 At, Advances it by 1 if the end of the buffer has been reached it moves it
 	 Back to the beginning of the buffer
 ******************************************************************************/
 void buffer_write(cyclic_buffer *cy, char c);

 /******************************************************************************
 buffer_write
 Description:
 	 The function receives a cyclic buffer to read from, returns the current char
 	 Read pointer pointing at and advances it by 1.if reached the end of the buffer
 	 It takes it back to the beginning
 ******************************************************************************/
 char buffer_read(cyclic_buffer *cy);

 /******************************************************************************
 buffer_isEmpty
 Description:
 	 Checks if the buffer is empty simply by checking if the read and write
 	 Pointers are pointing at the same address. returns true or false, receives
 	 A cyclic buffer
 ******************************************************************************/
 BOOL buffer_isEmpty(cyclic_buffer *cy);

#endif /* CYCLIC_BUFFER_H_ */
