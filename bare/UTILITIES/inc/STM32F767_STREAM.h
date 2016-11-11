//
//
//
//
//



#ifndef STM32F767_STREAM_H
#define STM32F767_STREAM_H

#include "stm32f7xx.h"
#include "STM32F767_BUFFER.h"


//Put pipe into hash table. Tasks need to know exactly what pipe they will be
//accessing. If the pipe doesn't exist then the task to handle to pipe doesn't
//exist and it needs to be created.

struct PIPE
{
  void *memorybuffer;

  uint8_t (*Read)(void *memorylocation, uint8_t *data);
  uint8_t (*Write)(void *memorylocation, uint8_t data);

  uint16_t num_connected;
  uint16_t flags;
};

typedef struct PIPE pip;



#endif
