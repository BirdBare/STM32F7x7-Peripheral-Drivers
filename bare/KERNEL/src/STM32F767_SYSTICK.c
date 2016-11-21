//
//
//
//
//



#include "stm32f7xx.h"
#include "STM32F767_SYSTICK.h"
#include "STM32F767_KERNEL.h"



volatile uint32_t SysTick_Ticks = 0;
volatile uint32_t SysTick_TicksPerMilli = 1;



void SysTick_Enable(uint32_t TicksPerInterrupt) 
{

  SysTick->LOAD = TicksPerInterrupt; /*Sets reload value*/ 
  
  SysTick_TicksPerMilli = (_FCPU / 1000) / TicksPerInterrupt;

  SysTick->CTRL |= (SysTick_CTRL_CLKSOURCE_Msk | 
                    SysTick_CTRL_TICKINT_Msk |
                    SysTick_CTRL_ENABLE_Msk); 
}

uint32_t SysTick_MilliSec(void)
{
  return SysTick_Ticks / SysTick_TicksPerMilli;
}

void DelayMilli(uint32_t Milli)
{
  uint32_t ref = SysTick_MilliSec();

  do
  {
    SCHEDULER_CallScheduler();
  } while((SysTick_MilliSec() - ref) < Milli);

}





