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

volatile uint16_t *LCD_Command = (volatile uint16_t *)0x60000000;

volatile uint16_t *LCD_Data = 
  (volatile uint16_t*)0b01100000000100000000000000000000;

static void LCD_EnablePins(GPIO_TypeDef *LCD_GPIOx, uint32_t LCD_Pins)
{
  GPIO_SetPins(LCD_GPIOx, LCD_Pins, GPIO_MODE_ALTERNATE, GPIO_OUTTYPE_PUSHPULL,
    GPIO_OUTSPEED_VHIGH, GPIO_PUPD_OFF, GPIO_ALTFUNCTION_12); 
}

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

static void LCD_EnableMemoryRegion(void)
{
  __DSB();
  MPU_Enable();
  MPU_SetRegion(7,0x60000000,1,0b11,0b010000,27);
  MPU_EnableRegion(7);
  __DSB();
}

#define LCD_Reset(void) \
  GPIO_SetOutput(GPIOE,LCD_RSTPIN); \
  GPIO_ResetOutput(GPIOE,LCD_RSTPIN); \
  GPIO_SetOutput(GPIOE,LCD_RSTPIN); \
  DelayMilli(30) 

static void LCD_EnableFMC(uint32_t FMC_BusWidth, uint32_t FMC_BusTurn,
  uint32_t FMC_DataSetup, uint32_t FMC_AddSetup)
{
  LCD_EnableMemoryRegion();
  //Makes Bank1 a device so all commands and data will be sent.  

  FMC_EnableClock();

  FMC_Bank1->BTCR[0] |= FMC_BCR1_WFDIS;

  FMC_EnableSRAM(FMC_SubBank_1, FMC_AsyncWait_OFF, FMC_ExtendedMode_OFF,
    FMC_WriteEnable_ON, FMC_WaitPolarity_LOW, FMC_BusWidth);

  FMC_SetTimingSRAM(FMC_SubBank_1, FMC_AccessMode_A, FMC_BusTurn,   
    FMC_DataSetup, FMC_AddSetup);

  FMC_EnableSubBank(FMC_SubBank_1);

}

static void LCD_WriteSetting(uint16_t LCD_SETTINGREG, uint16_t LCD_DATA)
{
  *LCD_Command = (uint16_t)LCD_SETTINGREG;
  *LCD_Data = (uint16_t)LCD_DATA;
}

#define DMA_CLOCK_DMA1 RCC_AHB1ENR_DMA1EN
#define DMA_CLOCK_DMA2 RCC_AHB1ENR_DMA2EN

#define DMA_EnableClock(DMA_CLOCK) RCC->AHB1ENR |= DMA_CLOCK 


#define LCD_WriteCommand(Command) *LCD_Command = (Command)
#define LCD_WriteData(Data) *LCD_Data = (Data)
#define LCD_ReadData(void) *LCD_Data

static void LCD_EnableDMA(void)
{
  RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;
  NVIC_EnableIRQ(DMA2_Stream0_IRQn);
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

}
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





#define DMA_PRIORITY_LOW 0
#define DMA_PRIORITY_MED DMA_SxCR_PL_0
#define DMA_PRIORITY_HIGH DMA_SxCR_PL_1
#define DMA_PRIORITY_VHIGH (DMA_SxCR_PL_0 | DMA_SxCR_PL_1)

#define DMA_DATAWIDTH_8 0
#define DMA_DATAWIDTH_16 0b1
#define DMA_DATAWIDTH_32 0b10

#define DMA_INCREMENT_ON 0b1
#define DMA_INCREMENT_OFF 0

static void DMA_EnableMem2Mem(DMA_Stream_TypeDef *DMAx_Streamx,
  uint32_t SourceAdd, uint32_t DestAdd, uint16_t DMA_DATAWIDTH, uint16_t numdata, 
  uint32_t DMA_PRIORITY, uint16_t DMA_INCREMENT)
{

  DMAx_Streamx->CR &= ~0b1;

  while((DMAx_Streamx->CR & DMA_SxCR_EN) != 0)
    asm("");

  DMAx_Streamx->NDTR = numdata;

  DMAx_Streamx->PAR = SourceAdd;
  DMAx_Streamx->M0AR = DestAdd;


  DMAx_Streamx->CR = (uint32_t)DMA_PRIORITY | (DMA_DATAWIDTH << 13) | 
    (DMA_DATAWIDTH << 11) | (DMA_INCREMENT << 10) | (DMA_INCREMENT << 9) | 
    DMA_SxCR_DIR_1;

  DMAx_Streamx->CR |= DMA_SxCR_EN;
}

#define DMA_EnableTranferCompleteInt(DMA_Stream_x) DMA_Stream_x |= DMA_SxCR_TCIE





#endif
