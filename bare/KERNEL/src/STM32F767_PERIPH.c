//
//
//
//
//


#include "STM32F767_PERIPH.h"
#include "STM32F767_SYSTICK.h"
#include "STM32F767_KERNEL.h"
#include "STM32F767_STREAM.h"

void PERIPH_WaitTillReset(volatile void *RegisterAddress, uint32_t flag)
{
  struct THREAD *thread = SCHEDULER_CurrentThread(&SCHEDULER);

  thread->flags &= ~THREAD_COMPSETRESET;
  thread->temp1 = (uint32_t)RegisterAddress;
  thread->temp2 = flag;

  thread->timeoutcount = SysTick_Ticks; 

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

  thread->flags |= THREAD_COMPSETRESET;
  thread->temp1 = (uint32_t)RegisterAddress;
  thread->temp2 = flag;

  thread->timeoutcount = SysTick_Ticks;

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


// PERIPH PIPE

#define PERIPH_NUM_PIPES 18

struct PIPE PERIPH_PIPE[PERIPH_NUM_PIPES] = { {0} };

struct PIPE* PERIPH_GetPipe(void *peripheral)
{
  switch((uint32_t) peripheral)
  {
    //USART
    case (uint32_t) USART1:
      return &PERIPH_PIPE[0];

    case (uint32_t) USART2:
      return &PERIPH_PIPE[1];

    case (uint32_t) USART3:
      return &PERIPH_PIPE[2];

    case (uint32_t) UART4:
      return &PERIPH_PIPE[3];

    case (uint32_t) UART5:
      return &PERIPH_PIPE[4];

    case (uint32_t) USART6:
      return &PERIPH_PIPE[5];

    case (uint32_t) UART7:
      return &PERIPH_PIPE[6];

    case (uint32_t) UART8:
      return &PERIPH_PIPE[7];
    //END USART

    //SPI
    case (uint32_t) SPI1:
      return &PERIPH_PIPE[8];

    case (uint32_t) SPI2:
      return &PERIPH_PIPE[9];

    case (uint32_t) SPI3:
      return &PERIPH_PIPE[10];

    case (uint32_t) SPI4:
      return &PERIPH_PIPE[11];

    case (uint32_t) SPI5:
      return &PERIPH_PIPE[12];

    case (uint32_t) SPI6:
      return &PERIPH_PIPE[13];
    //END SPI

    //I2C
    case (uint32_t) I2C1:
      return &PERIPH_PIPE[14];

    case (uint32_t) I2C2:
      return &PERIPH_PIPE[15];

    case (uint32_t) I2C3:
      return &PERIPH_PIPE[16];

    case (uint32_t) I2C4:
      return &PERIPH_PIPE[17];
    //END I2C

    //ADC 
    case (uint32_t) ADC1:
      return &PERIPH_PIPE[18];

    case (uint32_t) ADC2:
      return &PERIPH_PIPE[19];

    case (uint32_t) ADC3:
      return &PERIPH_PIPE[20];
    //END ADC

    default:
      return 0;
  }
}










