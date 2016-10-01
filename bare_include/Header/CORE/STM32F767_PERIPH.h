//
//
//
//
//

#ifndef STM32F767_PERIPH_H
#define STM32F767_PERIPH_H

#include "stm32f7xx.h"

extern void PERIPH_LoopTillFlagReset(volatile void *RegisterAddress, uint32_t flag);
extern void PERIPH_LoopTillFlagSet(volatile void *RegisterAddress, uint32_t flag);
extern uint32_t  PERIPH_CheckFlag(volatile void *RegisterAddress, uint32_t flag);


#endif
