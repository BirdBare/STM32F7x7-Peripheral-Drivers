//
//
//
//
//



#ifndef STM32F767_DMA2D_H
#define STM32F767_DMA2D_H

#include "stm32f7xx.h"
#include "STM32F767_FMC_LCD.h"


#define LCD_COLORMODE DMA2D_COLORMODE_RGB565
extern volatile uint16_t LCD_BUFFER[240*320] __attribute__ ((section ("._frame_buf")));
//Frame Buffer for the LCD

#define DMA2D_EnableClock(void) RCC->AHB1ENR |= RCC_AHB1ENR_DMA2DEN
#define DMA2D_DisableClock(void) RCC->AHB1ENR &= ~RCC_AHB1ENR_DMA2DEN

#define DMA2D_COLORMODE_RGB565 0b010

#define LCD_XYOOR(x, y) ((x) > 239 || (y) > 319)

#define DMA2D_Start(void) DMA2D->CR |= DMA2D_CR_START

 void DMA2D_DrawVLine(uint16_t x, uint16_t y, uint16_t h, uint16_t
 color);

void DMA2D_DrawHLine(uint16_t x, uint16_t y, uint16_t w, uint16_t color);

void DMA2D_FillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h,
  uint16_t color);

void DMA2D_CopyPixelMap(const uint16_t map[], uint16_t x, uint16_t y, uint16_t
w, uint16_t h);

void DMA2D_WaitTransfer(void);

#define RGB565 0b010
#define RGB332 0b101

void DMA2D_LoadCLUT(void);

void DMA2D_CopyPixelMapPFC(const uint8_t map[], uint16_t x, uint16_t y, uint16_t
w, uint16_t h);

void DMA2D_UpdateScreen(void);

#endif
