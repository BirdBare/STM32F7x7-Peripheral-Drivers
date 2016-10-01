//
//
//
//
//




#include "STM32F767_SYSTICK.h"

volatile uint32_t SysTick_MilliSec = 0;

void SysTick_EnableTimer(void)
{
  SysTick->LOAD = TICKS_1MilliSec; //Sets reload value
  SysTick->CTRL |= (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk |
    SysTick_CTRL_ENABLE_Msk);
}

void DelayMilli(uint32_t Milli)
{
  uint32_t ref = MilliSec();
  
  while(MilliSec() - ref < Milli)
    asm("");
}







