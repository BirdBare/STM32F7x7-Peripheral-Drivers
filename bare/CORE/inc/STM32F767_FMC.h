//
//
//
//
//



#ifndef STM32F767_FMC_H
#define STM32F767_FMC_H

#include "stm32f7xx.h"
#include "BARE_STM32F767.h"




#define FMC_NOR ((FMC_NOR_TypeDef *)FMC_Bank1_R_BASE)
#define FMC_NAND ((FMC_NAND_TypeDef *)FMC_Bank3_R_BASE)
#define FMC_SDRAM ((FMC_SDRAM_TypeDef *)FMC_Bank5_6_R_BASE)


typedef struct
{
  __IO uint32_t BCR1;     // 0x0  
  __IO uint32_t BTR1;     // 0x4   
  __IO uint32_t BCR2;     // 0x8  
  __IO uint32_t BTR2;     // 0xc 
  __IO uint32_t BCR3;     // 0x10   
  __IO uint32_t BTR3;     // 0x14   
  __IO uint32_t BCR4;     // 0x18   
  __IO uint32_t BTR4;     // 0x1c   

  uint32_t RESERVED0[24]; // 0x20 - 0x7c

  __IO uint32_t PCR;        /*!< NAND Flash control register,                       Address offset: 0x80 */
  __IO uint32_t SR;         /*!< NAND Flash FIFO status and interrupt register,     Address offset: 0x84 */
  __IO uint32_t PMEM;       /*!< NAND Flash Common memory space timing register,    Address offset: 0x88 */
  __IO uint32_t PATT;       /*!< NAND Flash Attribute memory space timing register, Address offset: 0x8C */
  uint32_t      RESERVED1;  /*!< Reserved, 0x90                                                          */
  __IO uint32_t ECCR;       /*!< NAND Flash ECC result registers,                   Address offset: 0x94 */


  uint32_t RESERVED2[27];   //0x98 - 0x100

  __IO uint32_t BWTR1;      // 0x104   
  
  uint32_t RESERVED3;       // 0x108    
  
  __IO uint32_t BWTR2;        // 0x10c   
  
  uint32_t RESERVED4;         // 0x110    
  
  __IO uint32_t BWTR3;        // 0x114   
  
  uint32_t RESERVED5;         // 0x118    

  __IO uint32_t BWTR4;        // 0x11c   
  
  uint32_t RESERVED6[8];      //0x120 - 0x13c

  __IO uint32_t SDCR1;        /*!< SDRAM Control registers ,      Address offset: 0x140-0x144  */
  __IO uint32_t SDCR2;        /*!< SDRAM Control registers ,      Address offset: 0x140-0x144  */
  __IO uint32_t SDTR1;        /*!< SDRAM Timing registers ,       Address offset: 0x148-0x14C  */
  __IO uint32_t SDTR2;        /*!< SDRAM Timing registers ,       Address offset: 0x148-0x14C  */
  __IO uint32_t SDCMR;       /*!< SDRAM Command Mode register,    Address offset: 0x150  */
  __IO uint32_t SDRTR;       /*!< SDRAM Refresh Timer register,   Address offset: 0x154  */
  __IO uint32_t SDSR;        /*!< SDRAM Status register,          Address offset: 0x158  */




} FMC_NOR_TypeDef; 
  

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

#define FMC_SubBank_1 1
#define FMC_SubBank_2 2
#define FMC_SubBank_3 3
#define FMC_SubBank_4 4

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

/*

#define FMC_SubBank_1 0
#define FMC_SubBank_2 1
#define FMC_SubBank_3 2
#define FMC_SubBank_4 3

void FMC_EnableSubBank(uint8_t FMC_SubBank);

void FMC_DisableSubBank(uint8_t FMC_SubBank);

void FMC_EnableSRAM(uint8_t FMC_SubBank, uint32_t FMC_AsyncWait,
  uint32_t FMC_ExtendedMode, uint32_t FMC_WriteEnable, 
  uint32_t FMC_WaitPolarity, uint32_t FMC_BusWidth);

void FMC_SetTimingSRAM(uint8_t FMC_SubBank, uint32_t FMC_AccessMode,
  uint32_t FMC_BusTurn, uint32_t FMC_DataSetup, uint32_t FMC_AddSetup);
*/

#define FMC_EnableSubBank(FMC_SubBank) \
  _FMC_EnableSubBank(FMC_SubBank)
#define _FMC_EnableSubBank(FMC_SubBank) \
  FMC_NOR_SetBitsBCR##FMC_SubBank(FMC_NOR, FMC_BCR1_MBKEN)

#define FMC_DisableSubBank(FMC_SubBank) \
  _FMC_DisableSubBank(FMC_SubBank)
#define _FMC_DisbleSubBank(FMC_SubBank) \
  FMC_NOR_ResetBitsBCR##FMC_SubBank(FMC_NOR, ~FMC_BCR1_MBKEN)

#define FMC_EnableSRAM(FMC_SubBank, FMC_BCRx, FMC_BTRx) \
  _FMC_EnableSRAM(FMC_SubBank, FMC_BCRx, FMC_BTRx) \
  
#define _FMC_EnableSRAM(FMC_SubBank, FMC_BCRx, FMC_BTRx) \
do \
{ \
  FMC_NOR_SetBCR##FMC_SubBank(FMC_NOR, FMC_BCRx); \
  FMC_NOR_SetBTR##FMC_SubBank(FMC_NOR, FMC_BTRx); \
} while(0)



















  //Register Functions
ALWAYS_INLINE void FMC_NOR_SetBCR1(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data);
ALWAYS_INLINE uint32_t FMC_NOR_GetBCR1(FMC_NOR_TypeDef *FMC_NORx);
ALWAYS_INLINE void FMC_NOR_SetBitsBCR1(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data);
ALWAYS_INLINE void FMC_NOR_ResetBitsBCR1(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data);

ALWAYS_INLINE void FMC_NOR_SetBTR1(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data);
ALWAYS_INLINE uint32_t FMC_NOR_GetBTR1(FMC_NOR_TypeDef *FMC_NORx);
ALWAYS_INLINE void FMC_NOR_SetBitsBTR1(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data);
ALWAYS_INLINE void FMC_NOR_ResetBitsBTR1(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data);

ALWAYS_INLINE void FMC_NOR_SetBCR2(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data);
ALWAYS_INLINE uint32_t FMC_NOR_GetBCR2(FMC_NOR_TypeDef *FMC_NORx);
ALWAYS_INLINE void FMC_NOR_SetBitsBCR2(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data);
ALWAYS_INLINE void FMC_NOR_ResetBitsBCR2(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data);

ALWAYS_INLINE void FMC_NOR_SetBTR2(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data);
ALWAYS_INLINE uint32_t FMC_NOR_GetBTR2(FMC_NOR_TypeDef *FMC_NORx);
ALWAYS_INLINE void FMC_NOR_SetBitsBTR2(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data);
ALWAYS_INLINE void FMC_NOR_ResetBitsBTR2(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data);

ALWAYS_INLINE void FMC_NOR_SetBCR3(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data);
ALWAYS_INLINE uint32_t FMC_NOR_GetBCR3(FMC_NOR_TypeDef *FMC_NORx);
ALWAYS_INLINE void FMC_NOR_SetBitsBCR3(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data);
ALWAYS_INLINE void FMC_NOR_ResetBitsBCR3(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data);

ALWAYS_INLINE void FMC_NOR_SetBTR3(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data);
ALWAYS_INLINE uint32_t FMC_NOR_GetBTR3(FMC_NOR_TypeDef *FMC_NORx);
ALWAYS_INLINE void FMC_NOR_SetBitsBTR3(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data);
ALWAYS_INLINE void FMC_NOR_ResetBitsBTR3(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data);

ALWAYS_INLINE void FMC_NOR_SetBCR4(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data);
ALWAYS_INLINE uint32_t FMC_NOR_GetBCR4(FMC_NOR_TypeDef *FMC_NORx);
ALWAYS_INLINE void FMC_NOR_SetBitsBCR4(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data);
ALWAYS_INLINE void FMC_NOR_ResetBitsBCR4(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data);

ALWAYS_INLINE void FMC_NOR_SetBTR4(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data);
ALWAYS_INLINE uint32_t FMC_NOR_GetBTR4(FMC_NOR_TypeDef *FMC_NORx);
ALWAYS_INLINE void FMC_NOR_SetBitsBTR4(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data);
ALWAYS_INLINE void FMC_NOR_ResetBitsBTR4(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data);

ALWAYS_INLINE void FMC_NOR_SetBWTR1(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data);
ALWAYS_INLINE uint32_t FMC_NOR_GetBWTR1(FMC_NOR_TypeDef *FMC_NORx);
ALWAYS_INLINE void FMC_NOR_SetBitsBWTR1(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data);
ALWAYS_INLINE void FMC_NOR_ResetBitsBWTR1(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data);

ALWAYS_INLINE void FMC_NOR_SetBWTR2(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data);
ALWAYS_INLINE uint32_t FMC_NOR_GetBWTR2(FMC_NOR_TypeDef *FMC_NORx);
ALWAYS_INLINE void FMC_NOR_SetBitsBWTR2(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data);
ALWAYS_INLINE void FMC_NOR_ResetBitsBWTR2(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data);

ALWAYS_INLINE void FMC_NOR_SetBWTR3(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data);
ALWAYS_INLINE uint32_t FMC_NOR_GetBWTR3(FMC_NOR_TypeDef *FMC_NORx);
ALWAYS_INLINE void FMC_NOR_SetBitsBWTR3(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data);
ALWAYS_INLINE void FMC_NOR_ResetBitsBWTR3(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data);

ALWAYS_INLINE void FMC_NOR_SetBWTR4(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data);
ALWAYS_INLINE uint32_t FMC_NOR_GetBWTR4(FMC_NOR_TypeDef *FMC_NORx);
ALWAYS_INLINE void FMC_NOR_SetBitsBWTR4(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data);
ALWAYS_INLINE void FMC_NOR_ResetBitsBWTR4(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data);





  //  FMC_NORx->BCR1 Functions 
ALWAYS_INLINE void FMC_NOR_SetBCR1(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data)
{
  FMC_NORx->BCR1 = Data;
}
ALWAYS_INLINE uint32_t FMC_NOR_GetBCR1(FMC_NOR_TypeDef *FMC_NORx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x0]" : "=r" (ret) : "r" (FMC_NORx));
  return ret;
}
ALWAYS_INLINE void FMC_NOR_SetBitsBCR1(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data)
{
  FMC_NORx->BCR1 |= Data;
}
ALWAYS_INLINE void FMC_NOR_ResetBitsBCR1(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data)
{
  FMC_NORx->BCR1 &= Data;
}



  //  FMC_NORx->BTR1 Functions 
ALWAYS_INLINE void FMC_NOR_SetBTR1(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data)
{
  FMC_NORx->BTR1 = Data;
}
ALWAYS_INLINE uint32_t FMC_NOR_GetBTR1(FMC_NOR_TypeDef *FMC_NORx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x4]" : "=r" (ret) : "r" (FMC_NORx));
  return ret;
}
ALWAYS_INLINE void FMC_NOR_SetBitsBTR1(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data)
{
  FMC_NORx->BTR1 |= Data;
}
ALWAYS_INLINE void FMC_NOR_ResetBitsBTR1(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data)
{
  FMC_NORx->BTR1 &= Data;
}



  //  FMC_NORx->BCR2 Functions 
ALWAYS_INLINE void FMC_NOR_SetBCR2(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data)
{
  FMC_NORx->BCR2 = Data;
}
ALWAYS_INLINE uint32_t FMC_NOR_GetBCR2(FMC_NOR_TypeDef *FMC_NORx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x8]" : "=r" (ret) : "r" (FMC_NORx));
  return ret;
}
ALWAYS_INLINE void FMC_NOR_SetBitsBCR2(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data)
{
  FMC_NORx->BCR2 |= Data;
}
ALWAYS_INLINE void FMC_NOR_ResetBitsBCR2(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data)
{
  FMC_NORx->BCR2 &= Data;
}



  //  FMC_NORx->BTR2 Functions 
ALWAYS_INLINE void FMC_NOR_SetBTR2(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data)
{
  FMC_NORx->BTR2 = Data;
}
ALWAYS_INLINE uint32_t FMC_NOR_GetBTR2(FMC_NOR_TypeDef *FMC_NORx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0xc]" : "=r" (ret) : "r" (FMC_NORx));
  return ret;
}
ALWAYS_INLINE void FMC_NOR_SetBitsBTR2(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data)
{
  FMC_NORx->BTR2 |= Data;
}
ALWAYS_INLINE void FMC_NOR_ResetBitsBTR2(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data)
{
  FMC_NORx->BTR2 &= Data;
}



  //  FMC_NORx->BCR3 Functions 
ALWAYS_INLINE void FMC_NOR_SetBCR3(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data)
{
  FMC_NORx->BCR3 = Data;
}
ALWAYS_INLINE uint32_t FMC_NOR_GetBCR3(FMC_NOR_TypeDef *FMC_NORx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x10]" : "=r" (ret) : "r" (FMC_NORx));
  return ret;
}
ALWAYS_INLINE void FMC_NOR_SetBitsBCR3(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data)
{
  FMC_NORx->BCR3 |= Data;
}
ALWAYS_INLINE void FMC_NOR_ResetBitsBCR3(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data)
{
  FMC_NORx->BCR3 &= Data;
}



  //  FMC_NORx->BTR3 Functions 
ALWAYS_INLINE void FMC_NOR_SetBTR3(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data)
{
  FMC_NORx->BTR3 = Data;
}
ALWAYS_INLINE uint32_t FMC_NOR_GetBTR3(FMC_NOR_TypeDef *FMC_NORx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x14]" : "=r" (ret) : "r" (FMC_NORx));
  return ret;
}
ALWAYS_INLINE void FMC_NOR_SetBitsBTR3(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data)
{
  FMC_NORx->BTR3 |= Data;
}
ALWAYS_INLINE void FMC_NOR_ResetBitsBTR3(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data)
{
  FMC_NORx->BTR3 &= Data;
}



  //  FMC_NORx->BCR4 Functions 
ALWAYS_INLINE void FMC_NOR_SetBCR4(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data)
{
  FMC_NORx->BCR4 = Data;
}
ALWAYS_INLINE uint32_t FMC_NOR_GetBCR4(FMC_NOR_TypeDef *FMC_NORx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x18]" : "=r" (ret) : "r" (FMC_NORx));
  return ret;
}
ALWAYS_INLINE void FMC_NOR_SetBitsBCR4(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data)
{
  FMC_NORx->BCR4 |= Data;
}
ALWAYS_INLINE void FMC_NOR_ResetBitsBCR4(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data)
{
  FMC_NORx->BCR4 &= Data;
}



  //  FMC_NORx->BTR4 Functions 
ALWAYS_INLINE void FMC_NOR_SetBTR4(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data)
{
  FMC_NORx->BTR4 = Data;
}
ALWAYS_INLINE uint32_t FMC_NOR_GetBTR4(FMC_NOR_TypeDef *FMC_NORx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x1c]" : "=r" (ret) : "r" (FMC_NORx));
  return ret;
}
ALWAYS_INLINE void FMC_NOR_SetBitsBTR4(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data)
{
  FMC_NORx->BTR4 |= Data;
}
ALWAYS_INLINE void FMC_NOR_ResetBitsBTR4(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data)
{
  FMC_NORx->BTR4 &= Data;
}



  //  FMC_NORx->BWTR1 Functions 
ALWAYS_INLINE void FMC_NOR_SetBWTR1(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data)
{
  FMC_NORx->BWTR1 = Data;
}
ALWAYS_INLINE uint32_t FMC_NOR_GetBWTR1(FMC_NOR_TypeDef *FMC_NORx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x104]" : "=r" (ret) : "r" (FMC_NORx));
  return ret;
}
ALWAYS_INLINE void FMC_NOR_SetBitsBWTR1(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data)
{
  FMC_NORx->BWTR1 |= Data;
}
ALWAYS_INLINE void FMC_NOR_ResetBitsBWTR1(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data)
{
  FMC_NORx->BWTR1 &= Data;
}



  //  FMC_NORx->BWTR2 Functions 
ALWAYS_INLINE void FMC_NOR_SetBWTR2(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data)
{
  FMC_NORx->BWTR2 = Data;
}
ALWAYS_INLINE uint32_t FMC_NOR_GetBWTR2(FMC_NOR_TypeDef *FMC_NORx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x10c]" : "=r" (ret) : "r" (FMC_NORx));
  return ret;
}
ALWAYS_INLINE void FMC_NOR_SetBitsBWTR2(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data)
{
  FMC_NORx->BWTR2 |= Data;
}
ALWAYS_INLINE void FMC_NOR_ResetBitsBWTR2(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data)
{
  FMC_NORx->BWTR2 &= Data;
}



  //  FMC_NORx->BWTR3 Functions 
ALWAYS_INLINE void FMC_NOR_SetBWTR3(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data)
{
  FMC_NORx->BWTR3 = Data;
}
ALWAYS_INLINE uint32_t FMC_NOR_GetBWTR3(FMC_NOR_TypeDef *FMC_NORx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x114]" : "=r" (ret) : "r" (FMC_NORx));
  return ret;
}
ALWAYS_INLINE void FMC_NOR_SetBitsBWTR3(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data)
{
  FMC_NORx->BWTR3 |= Data;
}
ALWAYS_INLINE void FMC_NOR_ResetBitsBWTR3(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data)
{
  FMC_NORx->BWTR3 &= Data;
}



  //  FMC_NORx->BWTR4 Functions 
ALWAYS_INLINE void FMC_NOR_SetBWTR4(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data)
{
  FMC_NORx->BWTR4 = Data;
}
ALWAYS_INLINE uint32_t FMC_NOR_GetBWTR4(FMC_NOR_TypeDef *FMC_NORx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x11c]" : "=r" (ret) : "r" (FMC_NORx));
  return ret;
}
ALWAYS_INLINE void FMC_NOR_SetBitsBWTR4(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data)
{
  FMC_NORx->BWTR4 |= Data;
}
ALWAYS_INLINE void FMC_NOR_ResetBitsBWTR4(FMC_NOR_TypeDef *FMC_NORx, uint32_t Data)
{
  FMC_NORx->BWTR4 &= Data;
}




























#endif
