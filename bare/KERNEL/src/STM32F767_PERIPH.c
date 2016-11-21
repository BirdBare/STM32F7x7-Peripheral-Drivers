//
//
//
//
//


#include "STM32F767_PERIPH.h"
#include "STM32F767_KERNEL.h"

void PERIPH_WaitTillReset(volatile void *RegisterAddress, uint32_t flag)
{
  struct THREAD *thread = SCHEDULER_CurrentThread(&SCHEDULER);

  thread->temp1 = (uint32_t)RegisterAddress;
  thread->temp2 = flag;

  thread->timeoutcount = 1;

  while((*(uint32_t *)RegisterAddress & flag) != 0)
  {
    SCHEDULER_CallScheduler();
  }

  thread->temp2 = 0;
  thread->timeoutcount = 0;
}
void PERIPH_WaitTillSet(volatile void *RegisterAddress, uint32_t flag)
{
  struct THREAD *thread = SCHEDULER_CurrentThread(&SCHEDULER);

  thread->temp1 = (uint32_t)RegisterAddress;
  thread->temp2 = flag;

  thread->timeoutcount = THREAD_COMPSETRESET | 1;

  while((*(uint32_t *)RegisterAddress & flag) == 0)
  {
    SCHEDULER_CallScheduler();
  }

  thread->temp2 = 0;
  thread->timeoutcount = 0;
}


uint32_t  PERIPH_GetStatus(volatile void *RegisterAddress, uint32_t flag)
{
 return *(volatile uint32_t *)RegisterAddress & flag;
}


