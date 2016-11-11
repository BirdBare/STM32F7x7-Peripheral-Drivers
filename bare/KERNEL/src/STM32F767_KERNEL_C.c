//
//
//
//
//



#include "STM32F767_KERNEL.h"
#include "STM32F767_SYSTICK.h"

volatile struct THREAD MAIN = {&MAIN,&MAIN,(uint32_t *)!0,0};

volatile struct SCHEDULER SCHEDULER = {&MAIN,SCHEDULER_HOLD};


// THE THREAD SWITCH FUNCTION.
__attribute__((section("._ITCM.SCHEDULING")))
  void* KERNEL_Switch(volatile struct SCHEDULER *sched,
    volatile struct THREAD *current, uint32_t currentthreadflags, 
    volatile struct THREAD *next)
{
  if(!(current->sp))
    bree((uint32_t *)current);

  current = current->next;
  sched->thread = current;
  SCB_InvalidateICache();
  
  return sched->thread->sp;
}

