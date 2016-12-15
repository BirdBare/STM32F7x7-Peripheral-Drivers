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

void SysTick_Handler(void)
{
  SysTick_Ticks++;
  //increment

  if((SCHEDULER.flags & (SCHEDULER_HOLD | SCHEDULER_SWHOLD)) == 0)
  {
    SCHEDULER_CallScheduler();
  }
  //only call if neither flag is set

  SCHEDULER.flags &= ~SCHEDULER_SWHOLD;
  //turn off scheduler switch hold. only on once so we will always disable.
}


void SysTick_Enable(uint32_t TicksPerInterrupt) 
{	
	if((SysTick->CTRL & SysTick_CTRL_ENABLE_Msk) == 0)
	{
		SysTick->LOAD = TicksPerInterrupt; /*Sets reload value*/ 
  
		SysTick_TicksPerMilli = (_FCPU / 1000) / TicksPerInterrupt;

		SysTick->CTRL |= (SysTick_CTRL_CLKSOURCE_Msk | 
                    SysTick_CTRL_TICKINT_Msk |
                    SysTick_CTRL_ENABLE_Msk); 
	}
}

uint32_t SysTick_MilliSec(void)
{
  return SysTick_Ticks / SysTick_TicksPerMilli;
}

void DelayMilli(uint32_t Milli)
{
  struct THREAD *thread = SCHEDULER_CurrentThread(&SCHEDULER);

  uint32_t ref = thread->temp1 = SysTick_MilliSec();

  thread->temp2 = Milli;
  
  do
  {
    SCHEDULER_CallScheduler();
  } while((SysTick_MilliSec() - ref) < Milli);

  thread->temp2 = 0;
}





