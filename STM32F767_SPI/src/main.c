//
//
//
//
//

#include "stm32f7xx.h"
#include "STM32F767_SYSTICK.h"
#include "STM32F767_SPI.h"
#include "STM32F767_GPIO.h"

#define SPI_SS GPIO_PIN_11
#define SPI_CLK GPIO_PIN_5
#define SPI_MOSI GPIO_PIN_7
#define SPI_MISO GPIO_PIN_6


int main(void)
{

  
  SysTick_EnableTimer();

  GPIO_EnableClock(GPIO_CLOCK_GPIOA);
  GPIO_EnableClock(GPIO_CLOCK_GPIOB);

  GPIO_SetPins(GPIOA, SPI_MISO | SPI_CLK | SPI_MOSI, GPIO_MODE_ALTERNATE, 
    GPIO_OUTTYPE_PUSHPULL, GPIO_OUTSPEED_VHIGH, GPIO_PUPD_OFF,
    GPIO_ALTFUNCTION_5);


  GPIO_EnableClock(GPIO_CLOCK_GPIOC);
  GPIO_SetPins(GPIOC,SPI_SS,GPIO_MODE_OUTPUT, GPIO_OUTTYPE_PUSHPULL,
    GPIO_OUTSPEED_VHIGH, GPIO_PUPD_OFF, GPIO_NO_USE);

  //Init Code

  GPIO_SetOutput(GPIOC,SPI_SS);

  SPI_EnableClockAPB2(SPI_CLOCK_SPI1);

  //SPI_EnableMaster(SPI1, SPI_CLOCKDIV_256, SPI_MODE_0, 8, SPI_LSBFIRST_MSB);


SPI_EnableMaster(SPI1, SPI_CR1_CLKDIV_256 | SPI_CR1_SPE | SPI_CR1_MSTR, 
                       SPI_CR2_FIFO_8bit | SPI_CR2_DSIZE_8,0);


loop:;

 // Microcontroller Repeat Code

uint16_t tdata = GPIO_GetOutState(GPIOC,SPI_SS) >> 11;

  GPIO_ToggleOutput(GPIOC,SPI_SS);
  PERIPH_LoopTillFlagSet(&SPI1->SR,2);
  SPI_Send8(SPI1,GPIO_GetOutState(GPIOC,SPI_SS));
  while(!PERIPH_CheckFlag(&SPI1->SR,2));
  SPI_Send8(SPI1,tdata);
  while(!PERIPH_CheckFlag(&SPI1->SR,1));
  SPI_Receive8(SPI1);
  while(!PERIPH_CheckFlag(&SPI1->SR,1));
  SPI_Receive8(SPI1);
  while(PERIPH_CheckFlag(&SPI1->SR,1 << 7));
  GPIO_ToggleOutput(GPIOC,SPI_SS);
  DelayMilli(1);



goto loop;


  return 1;
}


