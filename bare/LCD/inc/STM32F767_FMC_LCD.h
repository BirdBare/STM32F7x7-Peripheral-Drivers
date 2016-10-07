//
//
//
//
//



#ifndef STM32F767_FMC_LCD_H
#define STM32F767_FMC_LCD_H

#include "stm32f7xx.h"
#include "STM32F767_GPIO.h"
#include "STM32F767_FMC.h"
#include "STM32F767_MPU.h"

#define LCD_WIDTH 240
#define LCD_HEIGHT 320

#define LCD_RSTPIN GPIO_PIN_5

extern volatile uint16_t *LCD_Command;

extern volatile uint16_t *LCD_Data;

void LCD_EnablePins(GPIO_TypeDef *LCD_GPIOx, uint32_t LCD_Pins);

/*
  LCD_EnableGeneralPins(); 
Address Pin = PE3  

D0 = PD14
D1 = PD15
D2 = PD0
D3 = PD1
D4 = PE7
D5 = PE8
D6 = PE9
D7 = PE10
D8 = PE11
D9 = PE12
D10 = PE13
D11 = PE14
D12 = PE15
D13 = PD8
D14 = PD9
D15 = PD10

NE1 = PD7

NOE = PD4
NWE = PD5
*/
#define LCD_EnableGeneralPins(void) \
{ \
  GPIO_EnableClock(GPIO_CLOCK_GPIOD | GPIO_CLOCK_GPIOE); \
  \
  LCD_EnablePins(GPIOD, GPIO_PIN_5 | GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 | \
    GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_14 | \
    GPIO_PIN_15);  \
  LCD_EnablePins(GPIOE, GPIO_PIN_3 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | \
    GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | \
    GPIO_PIN_15); \
\
  GPIO_SetPins(GPIOE, LCD_RSTPIN, GPIO_MODE_OUTPUT, GPIO_OUTTYPE_PUSHPULL,\
    GPIO_OUTSPEED_VHIGH, GPIO_PUPD_OFF, GPIO_NO_USE); \
}

void LCD_EnableMemoryRegion(void);

#define LCD_Reset(void) \
  GPIO_SetOutput(GPIOE,LCD_RSTPIN); \
  GPIO_ResetOutput(GPIOE,LCD_RSTPIN); \
  GPIO_SetOutput(GPIOE,LCD_RSTPIN); \
  DelayMilli(30) 

void LCD_EnableFMC(uint32_t FMC_BusWidth, uint32_t FMC_BusTurn,
  uint32_t FMC_DataSetup, uint32_t FMC_AddSetup);

void LCD_WriteSetting(uint16_t LCD_SETTINGREG, uint16_t LCD_DATA);

#define DMA_CLOCK_DMA1 RCC_AHB1ENR_DMA1EN
#define DMA_CLOCK_DMA2 RCC_AHB1ENR_DMA2EN

#define DMA_EnableClock(DMA_CLOCK) RCC->AHB1ENR |= DMA_CLOCK 


#define LCD_WriteCommand(Command) *LCD_Command = (Command)
#define LCD_WriteData(Data) *LCD_Data = (Data)
#define LCD_ReadData(void) *LCD_Data

void LCD_EnableDMA(void);

void LCD_InitLCD(void);
void LCD_SetWindow(uint32_t x, uint32_t y, uint32_t w, uint32_t h);

#define DMA_PRIORITY_LOW 0
#define DMA_PRIORITY_MED DMA_SxCR_PL_0
#define DMA_PRIORITY_HIGH DMA_SxCR_PL_1
#define DMA_PRIORITY_VHIGH (DMA_SxCR_PL_0 | DMA_SxCR_PL_1)

#define DMA_DATAWIDTH_8 0
#define DMA_DATAWIDTH_16 0b1
#define DMA_DATAWIDTH_32 0b10

#define DMA_INCREMENT_ON 0b1
#define DMA_INCREMENT_OFF 0

void DMA_EnableMem2Mem(DMA_Stream_TypeDef *DMAx_Streamx,
  uint32_t SourceAdd, uint32_t DestAdd, uint16_t DMA_DATAWIDTH, uint16_t numdata, 
  uint32_t DMA_PRIORITY, uint16_t DMA_INCREMENT);

#define DMA_EnableTranferCompleteInt(DMA_Stream_x) DMA_Stream_x |= DMA_SxCR_TCIE





#endif
