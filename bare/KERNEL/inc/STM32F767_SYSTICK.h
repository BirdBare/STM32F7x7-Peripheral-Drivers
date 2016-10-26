//
//
//
//
//



#ifndef STM32F767_SYSTICK_H
#define STM32F767_SYSTICK_H

#include "stm32f7xx.h"

#define TICKS_1MilliSec (((SystemCoreClock)/1000) - 1)

extern volatile uint32_t SysTick_MilliSec;

#define SysTick_EnableTimer(void) \
{ \
  SysTick->LOAD = TICKS_1MilliSec; /*Sets reload value*/ \
  SysTick->CTRL |= (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | \
    SysTick_CTRL_ENABLE_Msk); \
}

#define MilliSec(void) SysTick_MilliSec

void DelayMilli(uint32_t Milli);







#endif
