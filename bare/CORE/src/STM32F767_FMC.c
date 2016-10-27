//
//
//
//
//




#include "STM32F767_FMC.h"

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
void FMC_EnableSubBank(uint8_t FMC_SubBank)
{
  FMC_Bank1->BTCR[FMC_SubBank << 1] |= FMC_BCR1_MBKEN;
}

void FMC_DisableSubBank(uint8_t FMC_SubBank)
{
  FMC_Bank1->BTCR[FMC_SubBank << 1] &= (~FMC_BCR1_MBKEN);
}

void FMC_EnableSRAM(uint8_t FMC_SubBank, uint32_t FMC_AsyncWait,
  uint32_t FMC_ExtendedMode, uint32_t FMC_WriteEnable, 
  uint32_t FMC_WaitPolarity, uint32_t FMC_BusWidth)
{
  FMC_Bank1->BTCR[FMC_SubBank << 1] = (FMC_AsyncWait | FMC_ExtendedMode | 
    FMC_WriteEnable | FMC_WaitPolarity | FMC_BusWidth | FMC_BCR1_MBKEN | 
    0b10000000 | FMC_BCR1_WFDIS); 
    //MemType is enable as SRAM
}

void FMC_SetTimingSRAM(uint8_t FMC_SubBank, uint32_t FMC_AccessMode,
  uint32_t FMC_BusTurn, uint32_t FMC_DataSetup, uint32_t FMC_AddSetup)
{
  FMC_Bank1->BTCR[(FMC_SubBank << 1) + 1] = (FMC_AccessMode |
    (FMC_BusTurn << 16) | (FMC_DataSetup << 8) | FMC_AddSetup);
}



















