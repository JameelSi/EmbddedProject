#include "types.h"
#include "cyclic_buffer.h"


 void buffer_init(cyclic_buffer *cy){
	 cy->write=cy->buffer;
	 cy->read=cy->buffer;
}

 void buffer_write(cyclic_buffer *cy, char c){
	 *(cy->write)=c;
	 // "push" the char to the buffer if end of buffer reached, reset it
	 if(++(cy->write)==(cy->buffer)+BUFFER_SIZE)
		 cy->write=cy->buffer;

 }
 char buffer_read(cyclic_buffer *cy){
	 char c=*(cy->read);
	 //"pull" the char from the buffer and return it, advance the pointer
	 if(++(cy->read)==cy->buffer+BUFFER_SIZE)
		 cy->read=cy->buffer;
	 return c;
 }

 BOOL buffer_isEmpty(cyclic_buffer *cy){
	 return cy->read==cy->write;
 }

