//
//
//
//
//



#ifndef STM32F767_MALLOC_H
#define STM32F767_MALLOC_H

#include "BARE_STM32F767.h"
#include "stm32f7xx.h"
#include "STM32F767_KERNEL.h"

struct HEAP_TABLE
{
	void *freeheap;
	uint32_t size;
};

struct ALLOC_TABLE
{
	void *heap;
  uint32_t size; //bit [31] is the free flag. 0 == in use, 1 == free
  struct ALLOC_TABLE *next;
};

/* BLOCK STRUCTURE

----- Dynamic block

  ALLOC_TABLE 12bytes
  Dynamically allocated data

----- end of block

*/

void InitHeap(void *start, uint32_t size);

#define balloc(size) kballoc(size,KERNEL_ProcessHeap)
void* kballoc(uint32_t size, struct HEAP_TABLE *MemArea);

void bree(void *blockaddress);

#endif
