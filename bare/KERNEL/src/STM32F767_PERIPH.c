//
//
//
//
//


#include "STM32F767_PERIPH.h"
#include "STM32F767_KERNEL.h"

void PERIPH_WaitTillReset(volatile void *RegisterAddress, uint32_t flag)
{
  while((*(uint32_t *)RegisterAddress & flag) != 0)
  {
    SCHEDULER_CallScheduler();
  }
}
void PERIPH_WaitTillSet(volatile void *RegisterAddress, uint32_t flag)
{
  while((*(uint32_t *)RegisterAddress & flag) == 0)
  {
    SCHEDULER_CallScheduler();
  }
}


uint32_t  PERIPH_GetStatus(volatile void *RegisterAddress, uint32_t flag)
{
 return *(volatile uint32_t *)RegisterAddress & flag;
}


