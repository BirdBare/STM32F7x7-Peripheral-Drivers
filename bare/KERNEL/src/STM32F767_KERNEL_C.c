//
//
//
//
//



#include "STM32F767_KERNEL.h"

volatile uint32_t SysTick_MilliSec = 0;

volatile struct NEW_THREAD MAIN = {&MAIN,&MAIN,(uint32_t *)!0,0};

volatile struct NEW_SCHEDULER SCHEDULER = {&MAIN,SCHEDULER_HOLD};


// THE THREAD SWITCH FUNCTION.
__attribute__((section("._ITCM.SCHEDULING")))
  void* KERNEL_Switch(volatile struct NEW_SCHEDULER *sched,
    volatile struct NEW_THREAD *current, uint32_t currentthreadflags, 
    volatile struct NEW_THREAD *next)
{
  if(!(current->sp))
    bree((uint32_t *)current);

  current = current->next;
  sched->thread = current;
  SCB_InvalidateICache();
  
  return sched->thread->sp;
}

