//
//
//
//
//



#ifndef STM32F767_STREAM_H
#define STM32F767_STREAM_H

#include "stm32f7xx.h"
#include "STM32F767_BUFFER.h"

struct PIPE
{
  void *memorybuffer;

  uint8_t (*IsEmpty)(void *memorylocation); 
  uint32_t (*Read)(void *memorylocation);
  void (*Write)(void *memorylocation, uint32_t data);

  uint32_t flags;
};

typedef struct PIPE pip;



#endif
