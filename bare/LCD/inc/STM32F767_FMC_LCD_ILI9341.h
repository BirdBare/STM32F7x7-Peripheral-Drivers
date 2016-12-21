//
//
//
//
//



#ifndef STM32F767_FMC_LCD_ILI9341_H
#define STM32F767_FMC_LCD_ILI9341_H

#include "stm32f7xx.h"
#include "BARE_STM32F767.h"
#include "STM32F767_FMC_LCD.h"
//#include "STM32F767_xxx.h"

#define LCD_WIDTH 240
#define LCD_HEIGHT 320

#define LCD_Reset(void) \
do \
{ \
  GPIO_ResetOutput(&GPIOEo,LCD_RSTPIN); \
	DelayMilli(1); \
  GPIO_SetOutput(&GPIOEo,LCD_RSTPIN); \
  DelayMilli(150); \
} while(0)



static void LCD_SetWindow(uint32_t x, uint32_t y, uint32_t w, uint32_t h)
{

LCD_WriteCommand(0x2A);
    LCD_WriteData(x >> 8);
    LCD_WriteData(x);
    LCD_WriteData(w >> 8);
    LCD_WriteData(w);
    LCD_WriteCommand(0x2B);
    LCD_WriteData(y >> 8);
    LCD_WriteData(y);
    LCD_WriteData(h >> 8);
    LCD_WriteData(h);
//set write window    

}


static void LCD_InitLCD(void)
{

  LCD_Reset();
  
  LCD_WriteCommand(0x11);
  LCD_WriteCommand(0x28);
  LCD_WriteSetting(0xC0,0x26);
  LCD_WriteSetting(0xC1,0x11);
  LCD_WriteCommand(0xC5);
  LCD_WriteData(0x35);
  LCD_WriteData(0x3E);
  LCD_WriteSetting(0xC7,0xBE);
  LCD_WriteCommand(0xB1);
  LCD_WriteData(0x00);
  LCD_WriteData(0x1B);
  LCD_WriteCommand(0xB6);
  LCD_WriteData(0x0A);
  LCD_WriteData(0x82);
  LCD_WriteData(0x27);
  LCD_WriteData(0x00);
  LCD_WriteSetting(0xB7,0x07);
  LCD_WriteSetting(0x3A,0x55);
  LCD_WriteSetting(0x36,(1<<3) | (1<<6));
  LCD_WriteCommand(0x29);

LCD_WriteCommand(0xF2);    // 3GAMMA CONTROL
    LCD_WriteData(0x00);    // 1. (disabled), 0x02 def.
   
    LCD_WriteCommand(0x26);    // GAMMA SET
    LCD_WriteData(0x01);    // 1. (default)
   
    LCD_WriteCommand(0xE0);    // POSITIVE GAMMA CORRECTION
    LCD_WriteData(0x0F);    // 1.
    LCD_WriteData(0x31);    // 2.
    LCD_WriteData(0x2B);    // 3.
    LCD_WriteData(0x0C);    // 4.
    LCD_WriteData(0x0E);    // 5.
    LCD_WriteData(0x08);    // 6.
    LCD_WriteData(0x4E);    // 7.
    LCD_WriteData(0xF1);    // 8.
    LCD_WriteData(0x37);    // 9.
    LCD_WriteData(0x07);    // 10.
    LCD_WriteData(0x10);    // 11.
    LCD_WriteData(0x03);    // 12.
    LCD_WriteData(0x0E);    // 13.
    LCD_WriteData(0x09);    // 14.
    LCD_WriteData(0x00);    // 15.
   
    LCD_WriteCommand(0xE1);    // NEGATIVE GAMMA CORRECTION
    LCD_WriteData(0x00);    // 1.
    LCD_WriteData(0x0E);    // 2.
    LCD_WriteData(0x14);    // 3.
    LCD_WriteData(0x03);    // 4.
    LCD_WriteData(0x11);    // 5.
    LCD_WriteData(0x07);    // 6.
    LCD_WriteData(0x31);    // 7.
    LCD_WriteData(0xC1);    // 8.
    LCD_WriteData(0x48);    // 9.
    LCD_WriteData(0x08);    // 10.
    LCD_WriteData(0x0F);    // 11.
    LCD_WriteData(0x0C);    // 12.
    LCD_WriteData(0x31);    // 13.
    LCD_WriteData(0x36);    // 14.
    LCD_WriteData(0x0F);    // 15.
    LCD_SetWindow(0,0,239,319);

}


#endif
