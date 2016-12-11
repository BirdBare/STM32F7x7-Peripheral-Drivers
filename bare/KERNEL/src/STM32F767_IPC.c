//
//
//
//
//



#include "STM32F767_IPC.h"

struct PIPE PERIPH_PIPES[118] = {{0}};


struct PIPE * IPC_GetPeriphPipe(void * PERIPH)
{
	uint32_t ReducedVal = (uint32_t)PERIPH % 10000;

	return &PERIPH_PIPES[TableOffsets[ReducedVal / T_VAL] + (ReducedVal % T_VAL)];
}


// HASH table row offset
int8_t TableOffsets[] =
{
  0,
 -1,
 10,
 -1,
  6,
 -1,
  7,
 -1,
  1,
  2,
 22,
 -1,
 67,
 22,
  4,
 -1,
  3,
  0,
 -1,
  0,
 35,
  6,
 -1,
  0,
  4,
  0,
 -1,
  0,
 -1,
  0,
 -1,
  2,
 -1,
  4,
 -1,
 17,
 16,
  1,
 -1,
 21,
 65,
 63,
 -1,
 17,
 49,
  9,
  0,
  0,
  2,
  2,
 -1,
 11,
  1,
  3,
 -1,
  1,
  0,
  1,
  1,
 -1,
  6,
 -1,
 -1,
 -1,
  1,
 -1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
 27,
 13,
  1,
  1,
 -1,
  2,
  0,
  3,
  0,
  0,
 -1,
 67,
 45,
 19,
 17,
 -1,
 -1,
 93,
 23,
 -1,
 -1,
  5,
};









