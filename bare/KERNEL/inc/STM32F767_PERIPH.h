//
//
//
//
//

#ifndef STM32F767_PERIPH_H
#define STM32F767_PERIPH_H

#include "stm32f7xx.h"

void PERIPH_WaitTillReset(volatile void *RegisterAddress, uint32_t flag);
void PERIPH_WaitTillSet(volatile void *RegisterAddress, uint32_t flag);
uint32_t  PERIPH_GetStatus(volatile void *RegisterAddress, uint32_t flag);


#endif
