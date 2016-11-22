//
//
//
//
//



#ifndef STM32F767_SYSTICK_H
#define STM32F767_SYSTICK_H

#include "stm32f7xx.h"

#define SysTick_EnableTimer(void) SysTick_Enable(_FCPU / 1000) 


extern volatile uint32_t SysTick_Ticks;

void SysTick_Enable(uint32_t TicksPerInterrupt);

uint32_t SysTick_MilliSec(void);

void DelayMilli(uint32_t Milli);

void SysTick_Handler(void);





#endif
