//
//
//
//
//

#ifndef STM32F767_PERIPH_H
#define STM32F767_PERIPH_H

#include "stm32f7xx.h"
#include "BARE_STM32F767.h"

ALWAYS_INLINE void PERIPH_WaitTillReset(volatile void *RegisterAddress, uint32_t flag)
{
  ASM(" 1: \n\
        ldr r2, [%0] \n\
        ldr r12, =0xe000ed04 \n\
        and r2, %1 \n\
        cmp %1, r2 \n\
      bne 2f \n\
        mov r3, #1 << 26 \n\
        str r3, [r12] \n\
      b 1b \n\
      2: \n\
      " ::"r" (RegisterAddress), "r"(flag) : "r12", "r2", "r3");

}
ALWAYS_INLINE void PERIPH_WaitTillSet(volatile void *RegisterAddress, uint32_t flag)
{
  ASM(" 1: \n\
        ldr r2, [%0] \n\
        ldr r12, =0xe000ed04 \n\
        and r2, %1 \n\
        cmp %1, r2 \n\
      beq 2f \n\
        mov r3, #1 << 26 \n\
        str r3, [r12] \n\
      b 1b \n\
      2: \n\
      " ::"r" (RegisterAddress), "r"(flag) : "r12", "r2", "r3");
}


ALWAYS_INLINE uint32_t  PERIPH_GetStatus(volatile void *RegisterAddress, uint32_t flag)
{
 return *(volatile uint32_t *)RegisterAddress & flag;
}


#endif
