//
//
//
//
//



#ifndef STM32F767_DMA2D_H
#define STM32F767_DMA2D_H

#include "stm32f7xx.h"
#include "STM32F767_FMC_LCD.h"
#include "STM32F767_PERIPH.h"

extern volatile uint16_t LCD_BUFFER[240*320];
//Frame Buffer for the LCD

extern const uint32_t DMA2D_CLUT[256];


  //Register Functions
ALWAYS_INLINE void DMA2D_SetCR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);
ALWAYS_INLINE uint32_t DMA2D_GetCR(DMA2D_TypeDef *DMA2Dx);
ALWAYS_INLINE void DMA2D_SetBitsCR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);
ALWAYS_INLINE void DMA2D_ResetBitsCR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);

ALWAYS_INLINE void DMA2D_SetISR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);
ALWAYS_INLINE uint32_t DMA2D_GetISR(DMA2D_TypeDef *DMA2Dx);
ALWAYS_INLINE void DMA2D_SetBitsISR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);
ALWAYS_INLINE void DMA2D_ResetBitsISR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);

ALWAYS_INLINE void DMA2D_SetIFCR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);
ALWAYS_INLINE uint32_t DMA2D_GetIFCR(DMA2D_TypeDef *DMA2Dx);
ALWAYS_INLINE void DMA2D_SetBitsIFCR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);
ALWAYS_INLINE void DMA2D_ResetBitsIFCR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);

ALWAYS_INLINE void DMA2D_SetFGMAR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);
ALWAYS_INLINE uint32_t DMA2D_GetFGMAR(DMA2D_TypeDef *DMA2Dx);
ALWAYS_INLINE void DMA2D_SetBitsFGMAR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);
ALWAYS_INLINE void DMA2D_ResetBitsFGMAR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);

ALWAYS_INLINE void DMA2D_SetFGOR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);
ALWAYS_INLINE uint32_t DMA2D_GetFGOR(DMA2D_TypeDef *DMA2Dx);
ALWAYS_INLINE void DMA2D_SetBitsFGOR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);
ALWAYS_INLINE void DMA2D_ResetBitsFGOR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);

ALWAYS_INLINE void DMA2D_SetBGMAR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);
ALWAYS_INLINE uint32_t DMA2D_GetBGMAR(DMA2D_TypeDef *DMA2Dx);
ALWAYS_INLINE void DMA2D_SetBitsBGMAR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);
ALWAYS_INLINE void DMA2D_ResetBitsBGMAR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);

ALWAYS_INLINE void DMA2D_SetBGOR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);
ALWAYS_INLINE uint32_t DMA2D_GetBGOR(DMA2D_TypeDef *DMA2Dx);
ALWAYS_INLINE void DMA2D_SetBitsBGOR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);
ALWAYS_INLINE void DMA2D_ResetBitsBGOR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);

ALWAYS_INLINE void DMA2D_SetFGPFCCR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);
ALWAYS_INLINE uint32_t DMA2D_GetFGPFCCR(DMA2D_TypeDef *DMA2Dx);
ALWAYS_INLINE void DMA2D_SetBitsFGPFCCR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);
ALWAYS_INLINE void DMA2D_ResetBitsFGPFCCR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);

ALWAYS_INLINE void DMA2D_SetFGCOLR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);
ALWAYS_INLINE uint32_t DMA2D_GetFGCOLR(DMA2D_TypeDef *DMA2Dx);
ALWAYS_INLINE void DMA2D_SetBitsFGCOLR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);
ALWAYS_INLINE void DMA2D_ResetBitsFGCOLR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);

ALWAYS_INLINE void DMA2D_SetBGPFCCR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);
ALWAYS_INLINE uint32_t DMA2D_GetBGPFCCR(DMA2D_TypeDef *DMA2Dx);
ALWAYS_INLINE void DMA2D_SetBitsBGPFCCR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);
ALWAYS_INLINE void DMA2D_ResetBitsBGPFCCR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);

ALWAYS_INLINE void DMA2D_SetBGCOLR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);
ALWAYS_INLINE uint32_t DMA2D_GetBGCOLR(DMA2D_TypeDef *DMA2Dx);
ALWAYS_INLINE void DMA2D_SetBitsBGCOLR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);
ALWAYS_INLINE void DMA2D_ResetBitsBGCOLR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);

ALWAYS_INLINE void DMA2D_SetFGCMAR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);
ALWAYS_INLINE uint32_t DMA2D_GetFGCMAR(DMA2D_TypeDef *DMA2Dx);
ALWAYS_INLINE void DMA2D_SetBitsFGCMAR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);
ALWAYS_INLINE void DMA2D_ResetBitsFGCMAR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);

ALWAYS_INLINE void DMA2D_SetBGCMAR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);
ALWAYS_INLINE uint32_t DMA2D_GetBGCMAR(DMA2D_TypeDef *DMA2Dx);
ALWAYS_INLINE void DMA2D_SetBitsBGCMAR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);
ALWAYS_INLINE void DMA2D_ResetBitsBGCMAR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);

ALWAYS_INLINE void DMA2D_SetOPFCCR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);
ALWAYS_INLINE uint32_t DMA2D_GetOPFCCR(DMA2D_TypeDef *DMA2Dx);
ALWAYS_INLINE void DMA2D_SetBitsOPFCCR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);
ALWAYS_INLINE void DMA2D_ResetBitsOPFCCR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);

ALWAYS_INLINE void DMA2D_SetOCOLR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);
ALWAYS_INLINE uint32_t DMA2D_GetOCOLR(DMA2D_TypeDef *DMA2Dx);
ALWAYS_INLINE void DMA2D_SetBitsOCOLR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);
ALWAYS_INLINE void DMA2D_ResetBitsOCOLR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);

ALWAYS_INLINE void DMA2D_SetOMAR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);
ALWAYS_INLINE uint32_t DMA2D_GetOMAR(DMA2D_TypeDef *DMA2Dx);
ALWAYS_INLINE void DMA2D_SetBitsOMAR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);
ALWAYS_INLINE void DMA2D_ResetBitsOMAR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);

ALWAYS_INLINE void DMA2D_SetOOR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);
ALWAYS_INLINE uint32_t DMA2D_GetOOR(DMA2D_TypeDef *DMA2Dx);
ALWAYS_INLINE void DMA2D_SetBitsOOR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);
ALWAYS_INLINE void DMA2D_ResetBitsOOR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);

ALWAYS_INLINE void DMA2D_SetNLR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);
ALWAYS_INLINE uint32_t DMA2D_GetNLR(DMA2D_TypeDef *DMA2Dx);
ALWAYS_INLINE void DMA2D_SetBitsNLR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);
ALWAYS_INLINE void DMA2D_ResetBitsNLR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);

ALWAYS_INLINE void DMA2D_SetLWR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);
ALWAYS_INLINE uint32_t DMA2D_GetLWR(DMA2D_TypeDef *DMA2Dx);
ALWAYS_INLINE void DMA2D_SetBitsLWR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);
ALWAYS_INLINE void DMA2D_ResetBitsLWR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);

ALWAYS_INLINE void DMA2D_SetAMTCR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);
ALWAYS_INLINE uint32_t DMA2D_GetAMTCR(DMA2D_TypeDef *DMA2Dx);
ALWAYS_INLINE void DMA2D_SetBitsAMTCR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);
ALWAYS_INLINE void DMA2D_ResetBitsAMTCR(DMA2D_TypeDef *DMA2Dx, uint32_t Data);













#define LCD_COLORMODE DMA2D_COLORMODE_RGB565

#define DMA2D_EnableClock(void) RCC->AHB1ENR |= RCC_AHB1ENR_DMA2DEN
#define DMA2D_DisableClock(void) RCC->AHB1ENR &= ~RCC_AHB1ENR_DMA2DEN

#define DMA2D_COLORMODE_RGB565 0b010

#define LCD_XYOOR(x, y) ((x) > 239 || (y) > 319)

#define DMA2D_Start(void) DMA2D->CR |= DMA2D_CR_START

/*
void DMA2D_DrawVLine(uint32_t x, uint32_t y, uint32_t h, uint32_t color);

void DMA2D_DrawHLine(uint32_t x, uint32_t y, uint32_t w, uint32_t color);

void DMA2D_FillRect(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t color);
*/


void DMA2D_CopyPixelMap(const uint16_t map[], uint32_t x, uint32_t y, uint32_t
w, uint32_t h);

//void DMA2D_WaitTransfer(void);
#define DMA2D_WaitTransfer(void) \
  PERIPH_WaitTillReset((uint32_t *)0x4002B000,1)

#define RGB565 0b010
#define RGB332 0b101

void DMA2D_LoadCLUT(void);

void DMA2D_CopyPixelMapPFC(const uint8_t map[], uint16_t x, uint16_t y, uint16_t
w, uint16_t h);

void DMA2D_UpdateScreen(void);

void DMA2D_WaitTransfer2(void);
/*
OPFCCR Colorformat
OCOLR  Color to write
OMAR   Write Address
NLR    NUMBER LINES and pixels
OOR    LINE OFFSET
*/

void DMA2D_Reg2Mem(uint32_t OMAR, uint32_t OPFCCR, uint32_t OCOLR,
  uint32_t NLR, uint32_t OOR);

/*
FGPFCCR Colorformat
OCOLR  Color to write
OMAR   Write Address
FGMAR  Input address
NLR    NUMBER LINES and pixels
OOR    LINE OFFSET
FGOR    LINE OFFSET
*/


void DMA2D_Mem2Mem(uint32_t FGMAR, uint32_t OMAR, uint32_t FGPFCCR, 
  uint32_t NLR, uint32_t FGOR, uint32_t OOR);


/*
FGPFCCR input Colorformat
OPFCCR  ouput color format
OCOLR  Color to write
OMAR   Write Address
FGMAR  Input address
NLR    NUMBER LINES and pixels
OOR    LINE OFFSET
FGOR    LINE OFFSET
*/

void DMA2D_Mem2MemPFC(uint32_t FGMAR, uint32_t OMAR, uint32_t FGPFCCR,
  uint32_t OPFCCR, uint32_t NLR, uint32_t FGOR, uint32_t OOR);


























  //  DMA2Dx->CR Functions 
ALWAYS_INLINE void DMA2D_SetCR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->CR = Data;
}
ALWAYS_INLINE uint32_t DMA2D_GetCR(DMA2D_TypeDef *DMA2Dx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x0]" : "=r" (ret) : "r" (DMA2Dx));
  return ret;
}
ALWAYS_INLINE void DMA2D_SetBitsCR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->CR |= Data;
}
ALWAYS_INLINE void DMA2D_ResetBitsCR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->CR &= Data;
}



  //  DMA2Dx->ISR Functions 
ALWAYS_INLINE void DMA2D_SetISR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->ISR = Data;
}
ALWAYS_INLINE uint32_t DMA2D_GetISR(DMA2D_TypeDef *DMA2Dx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x4]" : "=r" (ret) : "r" (DMA2Dx));
  return ret;
}
ALWAYS_INLINE void DMA2D_SetBitsISR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->ISR |= Data;
}
ALWAYS_INLINE void DMA2D_ResetBitsISR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->ISR &= Data;
}



  //  DMA2Dx->IFCR Functions 
ALWAYS_INLINE void DMA2D_SetIFCR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->IFCR = Data;
}
ALWAYS_INLINE uint32_t DMA2D_GetIFCR(DMA2D_TypeDef *DMA2Dx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x8]" : "=r" (ret) : "r" (DMA2Dx));
  return ret;
}
ALWAYS_INLINE void DMA2D_SetBitsIFCR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->IFCR |= Data;
}
ALWAYS_INLINE void DMA2D_ResetBitsIFCR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->IFCR &= Data;
}



  //  DMA2Dx->FGMAR Functions 
ALWAYS_INLINE void DMA2D_SetFGMAR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->FGMAR = Data;
}
ALWAYS_INLINE uint32_t DMA2D_GetFGMAR(DMA2D_TypeDef *DMA2Dx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0xc]" : "=r" (ret) : "r" (DMA2Dx));
  return ret;
}
ALWAYS_INLINE void DMA2D_SetBitsFGMAR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->FGMAR |= Data;
}
ALWAYS_INLINE void DMA2D_ResetBitsFGMAR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->FGMAR &= Data;
}



  //  DMA2Dx->FGOR Functions 
ALWAYS_INLINE void DMA2D_SetFGOR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->FGOR = Data;
}
ALWAYS_INLINE uint32_t DMA2D_GetFGOR(DMA2D_TypeDef *DMA2Dx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x10]" : "=r" (ret) : "r" (DMA2Dx));
  return ret;
}
ALWAYS_INLINE void DMA2D_SetBitsFGOR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->FGOR |= Data;
}
ALWAYS_INLINE void DMA2D_ResetBitsFGOR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->FGOR &= Data;
}



  //  DMA2Dx->BGMAR Functions 
ALWAYS_INLINE void DMA2D_SetBGMAR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->BGMAR = Data;
}
ALWAYS_INLINE uint32_t DMA2D_GetBGMAR(DMA2D_TypeDef *DMA2Dx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x14]" : "=r" (ret) : "r" (DMA2Dx));
  return ret;
}
ALWAYS_INLINE void DMA2D_SetBitsBGMAR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->BGMAR |= Data;
}
ALWAYS_INLINE void DMA2D_ResetBitsBGMAR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->BGMAR &= Data;
}



  //  DMA2Dx->BGOR Functions 
ALWAYS_INLINE void DMA2D_SetBGOR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->BGOR = Data;
}
ALWAYS_INLINE uint32_t DMA2D_GetBGOR(DMA2D_TypeDef *DMA2Dx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x18]" : "=r" (ret) : "r" (DMA2Dx));
  return ret;
}
ALWAYS_INLINE void DMA2D_SetBitsBGOR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->BGOR |= Data;
}
ALWAYS_INLINE void DMA2D_ResetBitsBGOR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->BGOR &= Data;
}



  //  DMA2Dx->FGPFCCR Functions 
ALWAYS_INLINE void DMA2D_SetFGPFCCR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->FGPFCCR = Data;
}
ALWAYS_INLINE uint32_t DMA2D_GetFGPFCCR(DMA2D_TypeDef *DMA2Dx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x1c]" : "=r" (ret) : "r" (DMA2Dx));
  return ret;
}
ALWAYS_INLINE void DMA2D_SetBitsFGPFCCR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->FGPFCCR |= Data;
}
ALWAYS_INLINE void DMA2D_ResetBitsFGPFCCR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->FGPFCCR &= Data;
}



  //  DMA2Dx->FGCOLR Functions 
ALWAYS_INLINE void DMA2D_SetFGCOLR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->FGCOLR = Data;
}
ALWAYS_INLINE uint32_t DMA2D_GetFGCOLR(DMA2D_TypeDef *DMA2Dx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x20]" : "=r" (ret) : "r" (DMA2Dx));
  return ret;
}
ALWAYS_INLINE void DMA2D_SetBitsFGCOLR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->FGCOLR |= Data;
}
ALWAYS_INLINE void DMA2D_ResetBitsFGCOLR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->FGCOLR &= Data;
}



  //  DMA2Dx->BGPFCCR Functions 
ALWAYS_INLINE void DMA2D_SetBGPFCCR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->BGPFCCR = Data;
}
ALWAYS_INLINE uint32_t DMA2D_GetBGPFCCR(DMA2D_TypeDef *DMA2Dx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x24]" : "=r" (ret) : "r" (DMA2Dx));
  return ret;
}
ALWAYS_INLINE void DMA2D_SetBitsBGPFCCR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->BGPFCCR |= Data;
}
ALWAYS_INLINE void DMA2D_ResetBitsBGPFCCR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->BGPFCCR &= Data;
}



  //  DMA2Dx->BGCOLR Functions 
ALWAYS_INLINE void DMA2D_SetBGCOLR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->BGCOLR = Data;
}
ALWAYS_INLINE uint32_t DMA2D_GetBGCOLR(DMA2D_TypeDef *DMA2Dx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x28]" : "=r" (ret) : "r" (DMA2Dx));
  return ret;
}
ALWAYS_INLINE void DMA2D_SetBitsBGCOLR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->BGCOLR |= Data;
}
ALWAYS_INLINE void DMA2D_ResetBitsBGCOLR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->BGCOLR &= Data;
}



  //  DMA2Dx->FGCMAR Functions 
ALWAYS_INLINE void DMA2D_SetFGCMAR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->FGCMAR = Data;
}
ALWAYS_INLINE uint32_t DMA2D_GetFGCMAR(DMA2D_TypeDef *DMA2Dx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x2c]" : "=r" (ret) : "r" (DMA2Dx));
  return ret;
}
ALWAYS_INLINE void DMA2D_SetBitsFGCMAR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->FGCMAR |= Data;
}
ALWAYS_INLINE void DMA2D_ResetBitsFGCMAR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->FGCMAR &= Data;
}



  //  DMA2Dx->BGCMAR Functions 
ALWAYS_INLINE void DMA2D_SetBGCMAR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->BGCMAR = Data;
}
ALWAYS_INLINE uint32_t DMA2D_GetBGCMAR(DMA2D_TypeDef *DMA2Dx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x30]" : "=r" (ret) : "r" (DMA2Dx));
  return ret;
}
ALWAYS_INLINE void DMA2D_SetBitsBGCMAR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->BGCMAR |= Data;
}
ALWAYS_INLINE void DMA2D_ResetBitsBGCMAR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->BGCMAR &= Data;
}



  //  DMA2Dx->OPFCCR Functions 
ALWAYS_INLINE void DMA2D_SetOPFCCR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->OPFCCR = Data;
}
ALWAYS_INLINE uint32_t DMA2D_GetOPFCCR(DMA2D_TypeDef *DMA2Dx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x34]" : "=r" (ret) : "r" (DMA2Dx));
  return ret;
}
ALWAYS_INLINE void DMA2D_SetBitsOPFCCR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->OPFCCR |= Data;
}
ALWAYS_INLINE void DMA2D_ResetBitsOPFCCR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->OPFCCR &= Data;
}



  //  DMA2Dx->OCOLR Functions 
ALWAYS_INLINE void DMA2D_SetOCOLR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->OCOLR = Data;
}
ALWAYS_INLINE uint32_t DMA2D_GetOCOLR(DMA2D_TypeDef *DMA2Dx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x38]" : "=r" (ret) : "r" (DMA2Dx));
  return ret;
}
ALWAYS_INLINE void DMA2D_SetBitsOCOLR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->OCOLR |= Data;
}
ALWAYS_INLINE void DMA2D_ResetBitsOCOLR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->OCOLR &= Data;
}



  //  DMA2Dx->OMAR Functions 
ALWAYS_INLINE void DMA2D_SetOMAR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->OMAR = Data;
}
ALWAYS_INLINE uint32_t DMA2D_GetOMAR(DMA2D_TypeDef *DMA2Dx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x3c]" : "=r" (ret) : "r" (DMA2Dx));
  return ret;
}
ALWAYS_INLINE void DMA2D_SetBitsOMAR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->OMAR |= Data;
}
ALWAYS_INLINE void DMA2D_ResetBitsOMAR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->OMAR &= Data;
}



  //  DMA2Dx->OOR Functions 
ALWAYS_INLINE void DMA2D_SetOOR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->OOR = Data;
}
ALWAYS_INLINE uint32_t DMA2D_GetOOR(DMA2D_TypeDef *DMA2Dx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x40]" : "=r" (ret) : "r" (DMA2Dx));
  return ret;
}
ALWAYS_INLINE void DMA2D_SetBitsOOR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->OOR |= Data;
}
ALWAYS_INLINE void DMA2D_ResetBitsOOR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->OOR &= Data;
}



  //  DMA2Dx->NLR Functions 
ALWAYS_INLINE void DMA2D_SetNLR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->NLR = Data;
}
ALWAYS_INLINE uint32_t DMA2D_GetNLR(DMA2D_TypeDef *DMA2Dx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x44]" : "=r" (ret) : "r" (DMA2Dx));
  return ret;
}
ALWAYS_INLINE void DMA2D_SetBitsNLR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->NLR |= Data;
}
ALWAYS_INLINE void DMA2D_ResetBitsNLR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->NLR &= Data;
}



  //  DMA2Dx->LWR Functions 
ALWAYS_INLINE void DMA2D_SetLWR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->LWR = Data;
}
ALWAYS_INLINE uint32_t DMA2D_GetLWR(DMA2D_TypeDef *DMA2Dx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x48]" : "=r" (ret) : "r" (DMA2Dx));
  return ret;
}
ALWAYS_INLINE void DMA2D_SetBitsLWR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->LWR |= Data;
}
ALWAYS_INLINE void DMA2D_ResetBitsLWR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->LWR &= Data;
}



  //  DMA2Dx->AMTCR Functions 
ALWAYS_INLINE void DMA2D_SetAMTCR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->AMTCR = Data;
}
ALWAYS_INLINE uint32_t DMA2D_GetAMTCR(DMA2D_TypeDef *DMA2Dx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x4c]" : "=r" (ret) : "r" (DMA2Dx));
  return ret;
}
ALWAYS_INLINE void DMA2D_SetBitsAMTCR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->AMTCR |= Data;
}
ALWAYS_INLINE void DMA2D_ResetBitsAMTCR(DMA2D_TypeDef *DMA2Dx, uint32_t Data)
{
  DMA2Dx->AMTCR &= Data;
}








#endif
