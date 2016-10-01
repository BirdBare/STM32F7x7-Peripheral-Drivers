//
//
//
//
//



#ifndef STM32F767_MPU_H
#define STM32F767_MPU_H

#include "stm32f7xx.h"

#define MPU_Enable(void) MPU->CTRL = (uint32_t)0b101
#define MPU_Disable(void) MPU->CTRL = (uint32_t)0

/* RegionNum IS FROM 0-7 */

/* MemoryAddressStart is the RegionSize Aligned memory address start */



#define MPU_SetRegion(RegionNum, MemoryAddressStart, InstructionFetch, \
  AccessPermissions, MemoryAccessAttributes, RegionSize) \
      MPU->RNR = RegionNum; \
      MPU->RBAR = MemoryAddressStart; \
      MPU->RASR = InstructionFetch << 28 | AccessPermissions << 24 | \
      MemoryAccessAttributes << 16 | RegionSize << 1

#define MPU_EnableRegion(RegionNum) \
  MPU->RNR = RegionNum; \
  MPU->RASR |= 1

#define MPU_DisableRegion(RegionNum) \
  MPU->RNR = RegionNum; \
  MPU->RASR &= ~1






#endif
