//
//
//
//
//



#include "STM32F767_KERNEL.h"

volatile struct NEW_THREAD MAIN = {(uint32_t *)!0,&MAIN,&MAIN,0};

volatile struct NEW_SCHEDULER SCHEDULER = {&MAIN,0};

volatile uint32_t *FPCARREG = &(FPU->FPCAR);


// FOR DEBUGGING A NO THREADS SITUATION. OR IT CAN RESTART THE MAIN TASK.
__attribute__((section("._ITCM.SCHEDULING")))
void KERNEL_NoThreads(void)
{
LOOP
}





// THE THREAD SWITCH FUNCTION.
__attribute__((section("._ITCM.SCHEDULING")))
  void* KERNEL_Switch(volatile struct NEW_SCHEDULER *sched,
    volatile struct NEW_THREAD *current, uint32_t currentthreadflags, 
    volatile struct NEW_THREAD *next)
{
  if(!(current->sp))
    bree((uint32_t *)current);

  current = current->next;
  sched->flags &= ~SCHEDULER_HOLD;
  sched->thread = current;
  //SCB_InvalidateICache();
  
  return sched->thread->sp;
}

