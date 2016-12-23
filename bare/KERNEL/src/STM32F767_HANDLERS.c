//
//
//
//
//



#include "STM32F767_HANDLERS.h"
#include "STM32F767_SYSTICK.h"
#include "STM32F767_KERNEL.h"




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


