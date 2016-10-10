//
//
//
//
//



#ifndef STM32F767_FMC_H
#define STM32F767_FMC_H

#include "stm32f7xx.h"

#define FMC_EnableClock(void) \
  RCC -> AHB3ENR |= RCC_AHB3ENR_FMCEN;

#define FMC_DisableClock(void) \
  RCC -> AHB3RSTR |= RCC_AHB3ENR_FMCEN;
//*****  RESET AND CLOCK CONTROL  ******

/*
  Parameter value ranges:
    AddSetup 0 - 15 (15 default) = number HCLK cycles
    AddHold 1 - 15 (15 default) = number HCLK cycles 
    DataSetup 1 - 255 (255 default) = number HCLK cycles 
    DataLatency 2 - 17 (17 default) = number CLK cycles 
    BusTurn 0 - 15 (15 default) = number HCLK cycles 
    ClkDiv 2 - 16 (16 default) = number HCLK cycles 


*/

#define FMC_SubBank_1 0
#define FMC_SubBank_2 1
#define FMC_SubBank_3 2
#define FMC_SubBank_4 3

#define FMC_WriteBurst_ON FMC_BCR1_CBURSTRW 
#define FMC_WriteBurst_OFF 0x0

#define FMC_PageSize_0 0x0
#define FMC_PageSize_128 (uint32_t)0x10000
#define FMC_PageSize_256 (uint32_t)0x20000
#define FMC_PageSize_512 (uint32_t)0x30000
#define FMC_PageSize_1024 (uint32_t)0x40000

#define FMC_AsyncWait_ON FMC_BCR1_ASYNCWAIT 
#define FMC_AsyncWait_OFF 0x0

#define FMC_ExtendedMode_ON FMC_BCR1_EXTMOD 
#define FMC_ExtendedMode_OFF 0x0

#define FMC_SyncWait_ON FMC_BCR1_WAITEN
#define FMC_SyncWait_OFF 0x0

#define FMC_WriteEnable_ON FMC_BCR1_WREN
#define FMC_WriteEnable_OFF 0x0

#define FMC_WaitConfig_BEFORE 0x0
#define FMC_WaitConfig_DURING FMC_BCR1_WAITCFG 

#define FMC_WrapMode_ON FMC_BCR1_WRAPMOD
#define FMC_WrapMode_OFF 0x0

#define FMC_WaitPolarity_LOW 0x0
#define FMC_WaitPolarity_HIGH FMC_BCR1_WAITPOL  

#define FMC_BurstEnable_ON FMC_BCR1_BURSTEN 
#define FMC_BurstEnable_OFF 0x0

#define FMC_FlashAccess_ON FMC_BCR1_FACCEN 
#define FMC_FlashAccess_OFF 0x0

#define FMC_BusWidth_8 0x0
#define FMC_BusWidth_16 FMC_BCR1_MWID_0 
#define FMC_BusWidth_32 FMC_BCR1_MWID_1 

#define FMC_MemType_SRAM 0x0
#define FMC_MemType_PSRAM FMC_BCR2_MTYP_0 
#define FMC_MemType_NOR FMC_BCR2_MTYP_1

#define FMC_MultiplexEnable_OFF 0x0
#define FMC_MultiplexEnable_ON

#define FMC_AccessMode_A 0x0 
#define FMC_AccessMode_B FMC_BTR1_ACCMOD_0
#define FMC_AccessMode_C FMC_BTR1_ACCMOD_1  
#define FMC_AccessMode_D (FMC_BTR1_ACCMOD_0 | FMC_BTR1_ACCMOD_1)  

void FMC_EnableSubBank(uint8_t FMC_SubBank);

void FMC_DisableSubBank(uint8_t FMC_SubBank);

void FMC_EnableSRAM(uint8_t FMC_SubBank, uint32_t FMC_AsyncWait,
  uint32_t FMC_ExtendedMode, uint32_t FMC_WriteEnable, 
  uint32_t FMC_WaitPolarity, uint32_t FMC_BusWidth);

void FMC_SetTimingSRAM(uint8_t FMC_SubBank, uint32_t FMC_AccessMode,
  uint32_t FMC_BusTurn, uint32_t FMC_DataSetup, uint32_t FMC_AddSetup);


#endif
