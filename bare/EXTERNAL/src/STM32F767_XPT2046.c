//
//
//
//
//


#include "STM32F767_XPT2046.h"

void XPT2046_EnableGeneral(void)
{
  GPIO_EnableClock(GPIO_CLOCK_GPIOA);
  GPIO_EnableClock(GPIO_CLOCK_GPIOC);
  SPI_EnableClockAPB2(SPI_CLOCK_SPI1);

  GPIO_Config(&GPIOCo, XPT2046_CS,GPIO_MODE_OUTPUT,
    GPIO_OUTTYPE_PUSHPULL,GPIO_OUTSPEED_VHIGH,GPIO_NO_USE,
    GPIO_NO_USE);
  //Enable Clock and set CS pin as output

  GPIO_SetOutput(GPIOC,XPT2046_CS);
  //disable device
 
  GPIO_Config(&GPIOAo,XPT2046_CLK | XPT2046_MISO | XPT2046_MOSI,
    GPIO_MODE_ALTERNATE, GPIO_OUTTYPE_PUSHPULL,GPIO_OUTSPEED_VHIGH,
    GPIO_PUPD_OFF, GPIO_ALTFUNCTION_5);
  //Set SPI pins

  //SPI_EnableMaster(SPI1,SPI_CLOCKDIV_64, SPI_MODE_0, 0);
  SPI_EnableMaster(SPI1, SPI_CR1_CLKDIV_64 | SPI_CR1_SPE | SPI_CR1_MSTR, 
    SPI_CR2_FIFO_8bit | SPI_CR2_DSIZE_8,0);
  //Enable SPI clock and SPI as master
}


uint32_t GetAxis(uint32_t XPT2046_AXIS, uint32_t numavg)
{
  GPIO_ToggleOutput(GPIOC,XPT2046_CS);

  //!!!!  16 CLOCK PER CONVERSION  !!!!!!

uint32_t dataavg = 0;
    uint32_t data = 0;
  for(uint32_t count = numavg + 1; count != 0; count--)
  { 

    SPI_Send8(SPI1,XPT2046_StartBit |  XPT2046_PDBITS | 
      XPT2046_AXIS);
    PERIPH_WaitTillSet(&SPI1->SR,SPI_SR_RXNE);
    data |= SPI_Receive8(SPI1) >> 3;
    
    SPI_Send8(SPI1,0b0);
    dataavg += data;
    PERIPH_WaitTillSet(&SPI1->SR,SPI_SR_RXNE);
    data = SPI_Receive8(SPI1) << 5;
  }

  dataavg /= numavg;
  PERIPH_WaitTillReset(&SPI1->SR,SPI_SR_BSY);
  
  GPIO_ToggleOutput(GPIOC,XPT2046_CS);

  return dataavg; 
}


uint16_t XPT2046_GetAxis(uint8_t XPT2046_AXIS, uint8_t numavg)
{
  GPIO_ToggleOutput(GPIOC,XPT2046_CS);

  uint16_t data;
  uint32_t dataavg = 0;

  //!!!!  16 CLOCK PER CONVERSION  !!!!!!

  for(uint8_t count = 0; count < numavg; count++)
  {
    SPI_Send8(SPI1,XPT2046_StartBit |  XPT2046_PDBITS | 
      XPT2046_AXIS);
    PERIPH_WaitTillSet(&SPI1->SR,SPI_SR_RXNE);
    data |= SPI_Receive8(SPI1) >> 3;
    
    SPI_Send8(SPI1,0b0);
    PERIPH_WaitTillSet(&SPI1->SR,SPI_SR_RXNE);
    data = SPI_Receive8(SPI1) << 5;
  
    if(count == numavg - 1)
    {
      SPI_Send8(SPI1,0b01);
      PERIPH_WaitTillSet(&SPI1->SR,SPI_SR_RXNE);
      data |= SPI_Receive8(SPI1) >> 3;
    }
    //get last bit of data without starting new conversion
 
    dataavg += data; 
  }

  dataavg /= numavg;
  
  GPIO_ToggleOutput(GPIOC,XPT2046_CS);

  return dataavg; 
}

void XPT2046_Begin(void)
{
  GPIO_ToggleOutput(GPIOC,XPT2046_CS);
  PERIPH_WaitTillSet(&SPI1->SR,SPI_SR_TXE);
  SPI_Send8(SPI1,XPT2046_StartBit | 0b0000 | XPT2046_PDBITS);
  GPIO_ToggleOutput(GPIOC,XPT2046_CS);
}
/*
#define XPT2046_Touched(void) (XPT2046_GetAxis(XPT2046_AXIS_Z2,1) < 3000 || \
  XPT2046_GetAxis(XPT2046_AXIS_Z1,1) > 300)

uint16_t con[4] = {3900,350,3850,260}; //top bottom right left

static void XPT2046_Calibrate(void)
{

  for(int i = 0; i<4; i++)
  {
    LCD_FillRect(0,0,240,320,0xfff);
    switch(i)
    {
      case 0:
        LCD_FillRect((float)(239/2) - (float)(2/2),0,2,2,0x0);
      break;

      case 1:
        LCD_FillRect((float)(239/2) - (float)(2/2),319,2,2,0x0);
      break;

      case 2:
        LCD_FillRect(239,(float)(319/2) - (float)(2/2),2,2,0x0);
      break;

      case 3:
        LCD_FillRect(0,(float)(319/2) - (float)(2/2),2,2,0x0);
      break;
    }
    LCD_UpdateScreen();
 
    while(!XPT2046_Touched())
    {
      asm("");
    } 
    
    if( i > 1)
    con[i] = XPT2046_GetAxis(XPT2046_AXIS_X,5);
    else 
    con[i] = XPT2046_GetAxis(XPT2046_AXIS_Y,5);

    //LCD_WriteXY(0,0,239,319);
    //LCD_WriteCommand(0x2C);

    //for(int i=0; i< 320*240; i++)
    //  LCD_WriteData(0xfff);

    LCD_FillRect(0,0,240,320,0xfff);
    LCD_UpdateScreen();

    while(XPT2046_Touched())
    {
      asm("");
    }

    DelayMilli(1000);
  }
}

static struct MATH_POINT XPT2046_GetPoint(void)
{
  struct MATH_POINT p;

//  p.x = 0.348330914 * ( XPT2046_GetAxis(XPT2046_AXIS_X,5)- 70);
//  p.y = 0.476190476 * ( XPT2046_GetAxis(XPT2046_AXIS_Y,5)- 69);

  p.x = NUMBERS_Map(XPT2046_GetAxis(XPT2046_AXIS_X,10) - con[3],con[2] - con[3],239); 

  p.y = 319 - NUMBERS_Map(XPT2046_GetAxis(XPT2046_AXIS_Y,10) - con[1],con[0] - con[1] ,319); 

  return p;
}
*/


