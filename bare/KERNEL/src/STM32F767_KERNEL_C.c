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
  void* KERNEL_SwitchHandler(volatile struct THREAD *current)
{
  current = current->next;
  SCHEDULER.thread = current;
  SCB_InvalidateICache();
  
  return SCHEDULER.thread->sp;
}

__attribute__((section("._ITCM.SCHEDULING")))
  void* KERNEL_DeleteHandler(volatile struct THREAD *thread)
{
  do
  {
    DLL_RemoveNode((void *)thread);
    bree((void *)thread);
    thread = thread->next;
  } while(thread->sp == 0);

  return (void *)thread->prev;
}

