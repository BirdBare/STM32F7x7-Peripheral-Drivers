//
//
//
//
//



#include "STM32F767_KERNEL.h"
#include "STM32F767_SYSTICK.h"

volatile struct THREAD MAIN = {&MAIN,&MAIN,(uint32_t *)!0,0,0,0,0};

volatile struct SCHEDULER SCHEDULER = {&MAIN,SCHEDULER_HOLD};


// THE THREAD SWITCH FUNCTION.
__attribute__((section("._ITCM.SCHEDULING")))
  void* KERNEL_SwitchHandler(volatile struct THREAD *current)
{
  uint32_t temp1;
  uint32_t temp2;
  uint32_t timeoutcount;

  do
  {
    if(current->sp == 0)
    {
      KERNEL_DeleteHandler(current);
    }

    current = current->next;

    temp1 = current->temp1;
    temp2 = current->temp2;
    timeoutcount = current->timeoutcount;

  } while(current->sp == 0  ||

          (timeoutcount != 0 && 
            !!(*(uint32_t *)temp1 & temp2) != 
            !!(timeoutcount & THREAD_COMPSETRESET)) ||

          (SysTick_MilliSec() - temp1) < temp2 ||

          0 );

  SCHEDULER.thread = current;

  SCB_InvalidateICache();
  
  return SCHEDULER.thread->sp;
}

__attribute__((section("._ITCM.SCHEDULING")))
  void KERNEL_DeleteHandler(volatile struct THREAD *thread)
{
    DLL_RemoveNode((void *)thread);
    bree((void *)thread);
}

