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

extern void SysTick_EnableTimer(void);
/*{
  SysTick->LOAD = TICKS_1MilliSec; //Sets reload value
  SysTick->CTRL |= (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk |
    SysTick_CTRL_ENABLE_Msk);
}*/

extern void SysTick_Handler(void);
/*{
  SysTick_MilliSec++; //1 Millisecond has passed.
}*/

#define MilliSec(void) SysTick_MilliSec

extern void DelayMilli(uint32_t Milli);
/*{
  uint32_t ref = MilliSec();
  
  while(MilliSec() - ref < Milli)
    asm("");
}*/







#endif
