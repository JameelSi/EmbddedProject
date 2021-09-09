#include "types.h"
#include "cyclic_buffer.h"
#include "eventQ.h"

static cyclic_buffer eventQ_cy;

 void eventQ_init(){
	 buffer_init(&eventQ_cy);
}

 void eventQ_write(uint32_t q){
	 buffer_write(&eventQ_cy, (char)q);
 }
 uint32_t eventQ_read(){
	 return (uint32_t)buffer_read(&eventQ_cy);
 }

 BOOL eventQ_isEmpty(){
	return buffer_isEmpty(&eventQ_cy);
 }

