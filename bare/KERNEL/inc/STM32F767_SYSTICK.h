//
//
//
//
//



#ifndef STM32F767_SYSTICK_H
#define STM32F767_SYSTICK_H

#include "stm32f7xx.h"

#define SysTick_EnableTimer(void) SysTick_Enable(_FCPU / 1000 - 1) 

void SysTick_Enable(uint32_t TicksPerInterrupt);

uint32_t SysTick_MilliSec(void);

void DelayMilli(uint32_t Milli);







#endif
