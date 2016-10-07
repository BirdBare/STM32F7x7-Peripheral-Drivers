//
//
//
//
//



#ifndef STM32F767_LCD_H
#define STM32F767_LCD_H

#include "stm32f7xx.h"


#include "STM32F767_DMA2D.h"
#include "STM32F767_MATH.h"
#include "STM32F767_FMC_LCD.h"

extern volatile uint16_t LCD_BUFFER[240*320] __attribute__((section("._frame_buf")));

#define DMA_ClearFlags(void)  DMA2->LIFCR |= DMA_LIFCR_CTCIF0 | DMA_LIFCR_CHTIF0

void DMA_WaitTransfer(DMA_Stream_TypeDef *DMAx_Streamx);

/*  Start LCD_UpdateScreen  */
uint8_t LCD_UpdateScreen(void);


/*  End LCD_UpdateScreen  */

#define LCD_DrawVLine(x, y, h, color) DMA2D_DrawVLine(x, y, h, color)
#define LCD_DrawHLine(x, y, w, color) DMA2D_DrawHLine(x, y, w, color)
#define LCD_FillRect(x, y, w, h, color) DMA2D_FillRect(x, y, w, h, color)
#define LCD_DrawPixel(x, y, color) if(!LCD_XYOOR(x,y)) LCD_BUFFER[(x) + (LCD_WIDTH * (y))] = color
 
#define swap(a,b) \
{ \
  int16_t swap = a; \
  a = b; \
  b = swap; \
}



void LCD_DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
  uint16_t color);

void LCD_DrawRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h,
  uint16_t color);

void LCD_FillCircle(uint16_t x, uint16_t y, uint16_t r, uint16_t color);

void LCD_DrawCircle(int16_t x, int16_t y, int16_t r, uint16_t color);

void LCD_DrawEllipse(int16_t x, int16_t y, int16_t a, int16_t b,
  uint16_t color) ;

void LCD_FillEllipse(int16_t x, int16_t y, int16_t a, int16_t b, 
  uint16_t color) ;

void LCD_DrawRoundRect(int16_t x, int16_t y, int16_t w,
 int16_t h, int16_t r, uint16_t color) ;

void LCD_FillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h,
int16_t r, 
  uint16_t color) ;

void LCD_DrawTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, 
  uint16_t x2, uint16_t y2, uint16_t color); 

void LCD_FillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, 
  int16_t x2, int16_t y2, uint16_t color) ;

//Draw XBitMap Files (*.xbm), exported from GIMP,
//Usage: Export from GIMP to *.xbm, rename *.xbm to *.c and open in editor.
//C Array can be directly used with this function
void LCD_DrawXBitmap(uint16_t x, uint16_t y,
 const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color) ;



/*
*******
*******
******

 START CHARACTER FUNCTIONS

*****
******
**
******
*/



#define FONT_ROCKWELL_18PT
#include "LCD_FONT.h"

uint32_t LCD_DrawChar3(uint16_t x, uint16_t y, uint16_t c, uint16_t color,
uint8_t size);



struct MATH_POINT LCD_PrintString(uint16_t x, uint16_t y, char *string, 
   uint16_t color, uint8_t size);

struct MATH_POINT LCD_PrintInt(int16_t x, int16_t y, uint32_t number, 
  uint16_t color, uint8_t size);

uint32_t GetIntLength(uint32_t num);

struct MATH_POINT LCD_PrintFloat(uint16_t x, uint16_t y, float number, 
  uint8_t precision, uint16_t color, uint8_t size);


struct MATH_POINT LCD_PrintfString(uint16_t x, uint16_t y, uint16_t w, 
  uint16_t h, char *string,  uint16_t color, uint8_t size);


#endif
