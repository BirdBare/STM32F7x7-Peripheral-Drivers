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










#endif
