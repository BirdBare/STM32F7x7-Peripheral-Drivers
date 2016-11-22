//
//
//
//
//


//special KERNEL function that deals with timeout tasks.
//task has flag that tells the kernel what to do to it on timeout
//kernel can reset or kill then notify the pipe.


#include "STM32F767_KERNEL.h"
#include "STM32F767_SYSTICK.h"

volatile struct THREAD MAIN = {&MAIN,&MAIN,(uint32_t *)!0};

volatile struct SCHEDULER SCHEDULER = {&MAIN,SCHEDULER_HOLD};

/*
// THE THREAD SWITCH FUNCTION.
__attribute__((section("._ITCM.SCHEDULING")))
  void* KERNEL_SwitchHandler(struct THREAD *current)
{
  uint32_t temp1;
  uint32_t temp2;
  uint32_t timeoutcount = current->timeoutcount;

 do
  {
    //if(0 && (timeoutcount & ~THREAD_COMPSETRESET) > timeoutmax)
    //{
      //KERNEL_TimeoutHandler(current);
    //}
    //else 
    if(current->sp == 0)
    {
      KERNEL_DeleteHandler(current);
    }

    current = (void *)current->next;

    temp1 = current->temp1;
    temp2 = current->temp2;
    timeoutcount = current->timeoutcount;

  } while((timeoutcount != 0 && 
            !!(*(uint32_t *)temp1 & temp2) != 
            !!(current->flags & THREAD_COMPSETRESET)) ||

          (SysTick_MilliSec() - temp1) < temp2 ||
            
          current->sp == 0  ||

          0 );



  SCHEDULER.thread = current;

  SCB_InvalidateICache();
  
  return SCHEDULER.thread->sp;
}
*/

__attribute__((section("._ITCM.SCHEDULING")))
  struct THREAD* KERNEL_DeleteHandler(struct THREAD *thread)
{
    DLL_RemoveNode((void *)thread);
    bree((void *)thread);
    return thread;
}

__attribute__((section("._ITCM.SCHEDULING")))
  struct THREAD* KERNEL_TimeoutHandler(struct THREAD *thread)
{
 
 while(10)
 asm("");

 return thread;


}

