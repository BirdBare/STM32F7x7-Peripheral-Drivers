//
//
//
//
//



#ifndef STM32F767_RCC_H
#define STM32F767_RCC_H

#include "BARE_STM32F767.h"

#define RCC_EnableClockAHB1(AHB1_CLOCK_x) \
  RCC_SetBitsAHB1ENR(RCC,AHB1_CLOCK_x)
#define RCC_EnableClockAHB2(AHB2_CLOCK_x) \
  RCC_SetBitsAHB2ENR(RCC,AHB2_CLOCK_x)
#define RCC_EnableClockAPB1(APB1_CLOCK_x) \
  RCC_SetBitsAPB1ENR(RCC,APB1_CLOCK_x)
#define RCC_EnableClockAPB2(APB2_CLOCK_x) \
  RCC_SetBitsAPB2ENR(RCC,APB2_CLOCK_x)

#define RCC_DisableClockAHB1(AHB1_CLOCK_x) \
  RCC_SetBitsAHB1RSTR(RCC,AHB1_CLOCK_x)
#define RCC_DisableClockAHB2(AHB2_CLOCK_x) \
  RCC_SetBitsAHB2RSTR(RCC,AHB2_CLOCK_x)
#define RCC_DisableClockAPB1(APB1_CLOCK_x) \
  RCC_SetBitsAPB1RSTR(RCC,APB1_CLOCK_x)
#define RCC_DisableClockAPB2(APB2_CLOCK_x) \
  RCC_SetBitsAPB2RSTR(RCC,APB2_CLOCK_x)



//  RCCx->CR functions
ALWAYS_INLINE void RCC_SetCR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->CR = Data;
}
ALWAYS_INLINE uint32_t RCC_GetCR(RCC_TypeDef *RCCx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1]" :"=r" (ret) : "r" (RCCx));
  return ret;
}
ALWAYS_INLINE void RCC_SetBitsCR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->CR |= Data;
}
ALWAYS_INLINE void RCC_ResetBitsCR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->CR &= Data;
}





//  RCCx->PLLGFGR functions
ALWAYS_INLINE void RCC_SetPLLCFGR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->PLLCFGR = Data;
}
ALWAYS_INLINE uint32_t RCC_GetPLLCFGR(RCC_TypeDef *RCCx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #4]" :"=r" (ret) : "r" (RCCx));
  return ret;
}
ALWAYS_INLINE void RCC_SetBitsPLLCFGR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->PLLCFGR |= Data;
}
ALWAYS_INLINE void RCC_ResetBitsPLLCFGR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->PLLCFGR &= Data;
}




//  RCCx->CR functions
ALWAYS_INLINE void RCC_SetCFGR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->CFGR = Data;
}
ALWAYS_INLINE uint32_t RCC_GetCFGR(RCC_TypeDef *RCCx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #8]" :"=r" (ret) : "r" (RCCx));
  return ret;
}
ALWAYS_INLINE void RCC_SetBitsCFGR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->CFGR |= Data;
}
ALWAYS_INLINE void RCC_ResetBitsCFGR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->CFGR &= Data;
}





//  RCCx->CR functions
ALWAYS_INLINE void RCC_SetCIR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->CIR = Data;
}
ALWAYS_INLINE uint32_t RCC_GetCIR(RCC_TypeDef *RCCx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0xc]" :"=r" (ret) : "r" (RCCx));
  return ret;
}
ALWAYS_INLINE void RCC_SetBitsCIR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->CIR |= Data;
}
ALWAYS_INLINE void RCC_ResetBitsCIR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->CIR &= Data;
}





//  RCCx->CR functions
ALWAYS_INLINE void RCC_SetAHB1RSTR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->AHB1RSTR = Data;
}
ALWAYS_INLINE uint32_t RCC_GetAHB1RSTR(RCC_TypeDef *RCCx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x10]" :"=r" (ret) : "r" (RCCx));
  return ret;
}
ALWAYS_INLINE void RCC_SetBitsAHB1RSTR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->AHB1RSTR |= Data;
}
ALWAYS_INLINE void RCC_ResetBitsAHB1RSTR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->AHB1RSTR &= Data;
}




//  RCCx->CR functions
ALWAYS_INLINE void RCC_SetAHB2RSTR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->AHB2RSTR = Data;
}
ALWAYS_INLINE uint32_t RCC_GetAHB2RSTR(RCC_TypeDef *RCCx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x14]" :"=r" (ret) : "r" (RCCx));
  return ret;
}
ALWAYS_INLINE void RCC_SetBitsAHB2RSTR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->AHB2RSTR |= Data;
}
ALWAYS_INLINE void RCC_ResetBitsAHB2RSTR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->AHB2RSTR &= Data;
}





//  RCCx->CR functions
ALWAYS_INLINE void RCC_SetAHB3RSTR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->AHB3RSTR = Data;
}
ALWAYS_INLINE uint32_t RCC_GetAHB3RSTR(RCC_TypeDef *RCCx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x18]" :"=r" (ret) : "r" (RCCx));
  return ret;
}
ALWAYS_INLINE void RCC_SetBitsAHB3RSTR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->AHB3RSTR |= Data;
}
ALWAYS_INLINE void RCC_ResetBitsAHB3RSTR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->AHB3RSTR &= Data;
}






//  RCCx->CR functions
ALWAYS_INLINE void RCC_SetAPB1RSTR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->APB1RSTR = Data;
}
ALWAYS_INLINE uint32_t RCC_GetAPB1RSTR(RCC_TypeDef *RCCx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x20]" :"=r" (ret) : "r" (RCCx));
  return ret;
}
ALWAYS_INLINE void RCC_SetBitsAPB1RSTR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->APB1RSTR |= Data;
}
ALWAYS_INLINE void RCC_ResetBitsAPB1RSTR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->APB1RSTR &= Data;
}






//  RCCx->CR functions
ALWAYS_INLINE void RCC_SetAPB2RSTR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->APB2RSTR = Data;
}
ALWAYS_INLINE uint32_t RCC_GetAPB2RSTR(RCC_TypeDef *RCCx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x24]" :"=r" (ret) : "r" (RCCx));
  return ret;
}
ALWAYS_INLINE void RCC_SetBitsAPB2RSTR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->APB2RSTR |= Data;
}
ALWAYS_INLINE void RCC_ResetBitsAPB2RSTR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->APB2RSTR &= Data;
}






//  RCCx->CR functions
ALWAYS_INLINE void RCC_SetAHB1ENR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->AHB1ENR = Data;
}
ALWAYS_INLINE uint32_t RCC_GetAHB1ENR(RCC_TypeDef *RCCx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x30]" :"=r" (ret) : "r" (RCCx));
  return ret;
}
ALWAYS_INLINE void RCC_SetBitsAHB1ENR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->AHB1ENR |= Data;
}
ALWAYS_INLINE void RCC_ResetBitsAHB1ENR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->AHB1ENR &= Data;
}





//  RCCx->CR functions
ALWAYS_INLINE void RCC_SetAHB2ENR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->AHB2ENR = Data;
}
ALWAYS_INLINE uint32_t RCC_GetAHB2ENR(RCC_TypeDef *RCCx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x34]" :"=r" (ret) : "r" (RCCx));
  return ret;
}
ALWAYS_INLINE void RCC_SetBitsAHB2ENR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->AHB2ENR |= Data;
}
ALWAYS_INLINE void RCC_ResetBitsAHB2ENR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->AHB2ENR &= Data;
}






//  RCCx->CR functions
ALWAYS_INLINE void RCC_SetAHB3ENR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->AHB3ENR = Data;
}
ALWAYS_INLINE uint32_t RCC_GetAHB3ENR(RCC_TypeDef *RCCx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x38]" :"=r" (ret) : "r" (RCCx));
  return ret;
}
ALWAYS_INLINE void RCC_SetBitsAHB3ENR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->AHB3ENR |= Data;
}
ALWAYS_INLINE void RCC_ResetBitsAHB3ENR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->AHB3ENR &= Data;
}






//  RCCx->CR functions
ALWAYS_INLINE void RCC_SetAPB1ENR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->APB1ENR = Data;
}
ALWAYS_INLINE uint32_t RCC_GetAPB1ENR(RCC_TypeDef *RCCx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x40]" :"=r" (ret) : "r" (RCCx));
  return ret;
}
ALWAYS_INLINE void RCC_SetBitsAPB1ENR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->APB1ENR |= Data;
}
ALWAYS_INLINE void RCC_ResetBitsAPB1ENR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->APB1ENR &= Data;
}






//  RCCx->CR functions
ALWAYS_INLINE void RCC_SetAPB2ENR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->APB2ENR = Data;
}
ALWAYS_INLINE uint32_t RCC_GetAPB2ENR(RCC_TypeDef *RCCx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x44]" :"=r" (ret) : "r" (RCCx));
  return ret;
}
ALWAYS_INLINE void RCC_SetBitsAPB2ENR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->APB2ENR |= Data;
}
ALWAYS_INLINE void RCC_ResetBitsAPB2ENR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->APB2ENR &= Data;
}








//  RCCx->CR functions
ALWAYS_INLINE void RCC_SetAHB1LPENR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->AHB1LPENR = Data;
}
ALWAYS_INLINE uint32_t RCC_GetAHB1LPENR(RCC_TypeDef *RCCx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x50]" :"=r" (ret) : "r" (RCCx));
  return ret;
}
ALWAYS_INLINE void RCC_SetBitsAHB1LPENR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->AHB1LPENR |= Data;
}
ALWAYS_INLINE void RCC_ResetBitsAHB1LPENR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->AHB1LPENR &= Data;
}





//  RCCx->CR functions
ALWAYS_INLINE void RCC_SetAHB2LPENR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->AHB2LPENR = Data;
}
ALWAYS_INLINE uint32_t RCC_GetAHB2LPENR(RCC_TypeDef *RCCx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x54]" :"=r" (ret) : "r" (RCCx));
  return ret;
}
ALWAYS_INLINE void RCC_SetBitsAHB2LPENR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->AHB2LPENR |= Data;
}
ALWAYS_INLINE void RCC_ResetBitsAHB2LPENR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->AHB2LPENR &= Data;
}






//  RCCx->CR functions
ALWAYS_INLINE void RCC_SetAHB3LPENR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->AHB3LPENR = Data;
}
ALWAYS_INLINE uint32_t RCC_GetAHB3LPENR(RCC_TypeDef *RCCx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x58]" :"=r" (ret) : "r" (RCCx));
  return ret;
}
ALWAYS_INLINE void RCC_SetBitsAHB3LPENR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->AHB3LPENR |= Data;
}
ALWAYS_INLINE void RCC_ResetBitsAHB3LPENR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->AHB3LPENR &= Data;
}






//  RCCx->CR functions
ALWAYS_INLINE void RCC_SetAPB1LPENR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->APB1LPENR = Data;
}
ALWAYS_INLINE uint32_t RCC_GetAPB1LPENR(RCC_TypeDef *RCCx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x60]" :"=r" (ret) : "r" (RCCx));
  return ret;
}
ALWAYS_INLINE void RCC_SetBitsAPB1LPENR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->APB1LPENR |= Data;
}
ALWAYS_INLINE void RCC_ResetBitsAPB1LPENR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->APB1LPENR &= Data;
}






//  RCCx->CR functions
ALWAYS_INLINE void RCC_SetAPB2LPENR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->APB2LPENR = Data;
}
ALWAYS_INLINE uint32_t RCC_GetAPB2LPENR(RCC_TypeDef *RCCx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x64]" :"=r" (ret) : "r" (RCCx));
  return ret;
}
ALWAYS_INLINE void RCC_SetBitsAPB2LPENR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->APB2LPENR |= Data;
}
ALWAYS_INLINE void RCC_ResetBitsAPB2LPENR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->APB2LPENR &= Data;
}





























//  RCCx->CR functions
ALWAYS_INLINE void RCC_SetBDCR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->BDCR = Data;
}
ALWAYS_INLINE uint32_t RCC_GetBDCR(RCC_TypeDef *RCCx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x70]" :"=r" (ret) : "r" (RCCx));
  return ret;
}
ALWAYS_INLINE void RCC_SetBitsBDCR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->BDCR |= Data;
}
ALWAYS_INLINE void RCC_ResetBitsBDCR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->BDCR &= Data;
}





//  RCCx->CR functions
ALWAYS_INLINE void RCC_SetCSR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->CSR = Data;
}
ALWAYS_INLINE uint32_t RCC_GetCSR(RCC_TypeDef *RCCx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x74]" :"=r" (ret) : "r" (RCCx));
  return ret;
}
ALWAYS_INLINE void RCC_SetBitsCSR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->CSR |= Data;
}
ALWAYS_INLINE void RCC_ResetBitsCSR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->CSR &= Data;
}





//  RCCx->CR functions
ALWAYS_INLINE void RCC_SetSSCGR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->SSCGR = Data;
}
ALWAYS_INLINE uint32_t RCC_GetSSCGR(RCC_TypeDef *RCCx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x80]" :"=r" (ret) : "r" (RCCx));
  return ret;
}
ALWAYS_INLINE void RCC_SetBitsSSCGR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->SSCGR |= Data;
}
ALWAYS_INLINE void RCC_ResetBitsSSCGR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->SSCGR &= Data;
}





//  RCCx->CR functions
ALWAYS_INLINE void RCC_SetPLLI2SCFGR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->PLLI2SCFGR = Data;
}
ALWAYS_INLINE uint32_t RCC_GetPLLI2SCFGR(RCC_TypeDef *RCCx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x84]" :"=r" (ret) : "r" (RCCx));
  return ret;
}
ALWAYS_INLINE void RCC_SetBitsPLLI2SCFGR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->PLLI2SCFGR |= Data;
}
ALWAYS_INLINE void RCC_ResetBitsPLLI2SCFGR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->PLLI2SCFGR &= Data;
}



//  RCCx->CR functions
ALWAYS_INLINE void RCC_SetPLLSAICFGR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->PLLSAICFGR = Data;
}
ALWAYS_INLINE uint32_t RCC_GetPLLSAICFGR(RCC_TypeDef *RCCx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x88]" :"=r" (ret) : "r" (RCCx));
  return ret;
}
ALWAYS_INLINE void RCC_SetBitsPLLSAICFGR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->PLLSAICFGR |= Data;
}
ALWAYS_INLINE void RCC_ResetBitsPLLSAICFGR(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->PLLSAICFGR &= Data;
}














//  RCCx->CR functions
ALWAYS_INLINE void RCC_SetDCKCFGR1(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->DCKCFGR1 = Data;
}
ALWAYS_INLINE uint32_t RCC_GetDCKCFGR1(RCC_TypeDef *RCCx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x8c]" :"=r" (ret) : "r" (RCCx));
  return ret;
}
ALWAYS_INLINE void RCC_SetBitsDCKCFGR1(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->DCKCFGR1 |= Data;
}
ALWAYS_INLINE void RCC_ResetBitsDCKCFGR1(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->DCKCFGR1 &= Data;
}




//  RCCx->CR functions
ALWAYS_INLINE void RCC_SetDCKCFGR2(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->DCKCFGR2 = Data;
}
ALWAYS_INLINE uint32_t RCC_GetDCKCFGR2(RCC_TypeDef *RCCx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x90]" :"=r" (ret) : "r" (RCCx));
  return ret;
}
ALWAYS_INLINE void RCC_SetBitsDCKCFGR2(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->DCKCFGR2 |= Data;
}
ALWAYS_INLINE void RCC_ResetBitsDCKCFGR2(RCC_TypeDef *RCCx, uint32_t Data)
{
  RCCx->DCKCFGR2 &= Data;
}

























#endif
