//
//
//
//
//



#ifndef STM32F767_MPU_H
#define STM32F767_MPU_H

#include "BARE_STM32F767.h"


ALWAYS_INLINE uint32_t MPU_GetType(MPU_Type *MPUx);
ALWAYS_INLINE void MPU_SetCTRL(MPU_Type *MPUx, uint32_t Data);
ALWAYS_INLINE uint32_t MPU_GetCTRL(MPU_Type *MPUx);
ALWAYS_INLINE void MPU_SetBitsCTRL(MPU_Type *MPUx, uint32_t Data);
ALWAYS_INLINE void MPU_ResetBitsCTRL(MPU_Type *MPUx, uint32_t Data);


ALWAYS_INLINE void MPU_SetRNR(MPU_Type *MPUx, uint32_t Data);
ALWAYS_INLINE uint32_t MPU_GetRNR(MPU_Type *MPUx);
ALWAYS_INLINE void MPU_SetBitsRNR(MPU_Type *MPUx, uint32_t Data);
ALWAYS_INLINE void MPU_ResetBitsRNR(MPU_Type *MPUx, uint32_t Data);


ALWAYS_INLINE void MPU_SetRBAR(MPU_Type *MPUx, uint32_t Data);
ALWAYS_INLINE uint32_t MPU_GetRBAR(MPU_Type *MPUx);
ALWAYS_INLINE void MPU_SetBitsRBAR(MPU_Type *MPUx, uint32_t Data);
ALWAYS_INLINE void MPU_ResetBitsRBAR(MPU_Type *MPUx, uint32_t Data);


ALWAYS_INLINE void MPU_SetRASR(MPU_Type *MPUx, uint32_t Data);
ALWAYS_INLINE uint32_t MPU_GetRASR(MPU_Type *MPUx);
ALWAYS_INLINE void MPU_SetBitsRASR(MPU_Type *MPUx, uint32_t Data);
ALWAYS_INLINE void MPU_ResetBitsRASR(MPU_Type *MPUx, uint32_t Data);



#define MPU_Enable(void) MPU_SetCTRL(MPU, 0b101)
#define MPU_Disable(void) MPU_SetCTRL(MPU, 0)

/* RegionNum IS FROM 0-7 */

/* MemoryAddressStart is the RegionSize Aligned memory address start */









#define MPU_SetRegion(RegionNum, MemoryAddressStart, InstructionFetch, \
  AccessPermissions, MemoryAccessAttributes, RegionSize) \
      MPU_SetRNR(MPU, RegionNum); \
      MPU_SetRBAR(MPU, MemoryAddressStart); \
      MPU_SetRASR(MPU, ((InstructionFetch) << 28) | ((AccessPermissions) << 24) | ((MemoryAccessAttributes) << 16) | ((RegionSize << 1)))

#define MPU_EnableRegion(RegionNum) \
  MPU_SetRNR(MPU, RegionNum); \
  MPU_SetBitsRASR(MPU, 1)

#define MPU_DisableRegion(RegionNum) \
  MPU_SetRNR(MPU, RegionNum); \
  MPU_ResetBitsRASR(MPU, ~1)








ALWAYS_INLINE uint32_t MPU_GetType(MPU_Type *MPUx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1]" : "=r" (ret) : "r" (MPU));
  return ret;
}







ALWAYS_INLINE void MPU_SetCTRL(MPU_Type *MPUx, uint32_t Data)
{
  MPU->CTRL = Data;
}
ALWAYS_INLINE uint32_t MPU_GetCTRL(MPU_Type *MPUx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #4]" : "=r" (ret) : "r" (MPU));
  return ret;
}
ALWAYS_INLINE void MPU_SetBitsCTRL(MPU_Type *MPUx, uint32_t Data)
{
  MPU->CTRL |= Data;
}
ALWAYS_INLINE void MPU_ResetBitsCTRL(MPU_Type *MPUx, uint32_t Data)
{
  MPU->CTRL &= Data;
}



ALWAYS_INLINE void MPU_SetRNR(MPU_Type *MPUx, uint32_t Data)
{
  MPU->RNR = Data;
}
ALWAYS_INLINE uint32_t MPU_GetRNR(MPU_Type *MPUx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #8]" : "=r" (ret) : "r" (MPU));
  return ret;
}
ALWAYS_INLINE void MPU_SetBitsRNR(MPU_Type *MPUx, uint32_t Data)
{
  MPU->RNR |= Data;
}
ALWAYS_INLINE void MPU_ResetBitsRNR(MPU_Type *MPUx, uint32_t Data)
{
  MPU->RNR &= Data;
}





ALWAYS_INLINE void MPU_SetRBAR(MPU_Type *MPUx, uint32_t Data)
{
  MPU->RBAR = Data;
}
ALWAYS_INLINE uint32_t MPU_GetRBAR(MPU_Type *MPUx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0xc]" : "=r" (ret) : "r" (MPU));
  return ret;
}
ALWAYS_INLINE void MPU_SetBitsRBAR(MPU_Type *MPUx, uint32_t Data)
{
  MPU->RBAR |= Data;
}
ALWAYS_INLINE void MPU_ResetBitsRBAR(MPU_Type *MPUx, uint32_t Data)
{
  MPU->RBAR &= Data;
}





ALWAYS_INLINE void MPU_SetRASR(MPU_Type *MPUx, uint32_t Data)
{
  MPU->RASR = Data;
}
ALWAYS_INLINE uint32_t MPU_GetRASR(MPU_Type *MPUx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x10]" : "=r" (ret) : "r" (MPU));
  return ret;
}
ALWAYS_INLINE void MPU_SetBitsRASR(MPU_Type *MPUx, uint32_t Data)
{
  MPU->RASR |= Data;
}
ALWAYS_INLINE void MPU_ResetBitsRASR(MPU_Type *MPUx, uint32_t Data)
{
  MPU->RASR &= Data;
}











#endif
