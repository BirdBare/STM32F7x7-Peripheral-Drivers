//
//
//
//
//

#include "stm32f7xx.h"
#include "STM32F767_SYSTICK.h"
#include "STM32F767_GPIO.h"
#include "STM32F767_I2C.h"


#define SCLK GPIO_PIN_6
#define SDA GPIO_PIN_7

int main(void)
{

SysTick_EnableTimer();

GPIO_EnableClock(GPIO_CLOCK_GPIOB);

GPIO_SetPins(GPIOB,SCLK | SDA, GPIO_MODE_ALTERNATE, GPIO_OUTTYPE_OPENDRAIN,
  GPIO_OUTSPEED_VHIGH, GPIO_PUPD_PU, GPIO_ALTFUNCTION_4);
 


I2C_EnableClock(I2C_CLOCK_I2C1);

I2C_EnableMaster(I2C1,I2C_CR1_PE, 8000,0);

GPIO_SetOutput(GPIOB,GPIO_PIN_1);

  //Init Code

loop:

 // Microcontroller Repeat Code

if(I2C_Start(I2C1, I2C_CR2_AUTOEND | I2C_CR2_WRITE | I2C_CR2_START, 0b10000000, 1))
{
  I2C_Send(I2C1,0xfe);
}

DelayMilli(20);

goto loop;


  return 1;
}


