//
//
//
//
//



#ifndef STM32F767_MALLOC_H
#define STM32F767_MALLOC_H

#include "BARE_STM32F767.h"
#include "stm32f7xx.h"

#define HEAPMINBOUNDRY 0x20000000

#define HEAPMAXSIZE (1024 * 50)
#define MAXSIZE_BITS (MALLOC_BIT31 - 1)
#define MALLOC_BIT31 ((uint32_t)0x80000000)

struct ALLOC_TABLE
{
  uint32_t size; //bit [31] is the free flag. 0 == in use, 1 == free
  struct ALLOC_TABLE *next;
};

/* BLOCK STRUCTURE

----- Dynamic block

  ALLOC_TABLE 12bytes
  Dynamically allocated data

----- end of block

*/

void InitHeap(void);

void* balloc(uint32_t size);

void bree(void *blockaddress);

#endif
