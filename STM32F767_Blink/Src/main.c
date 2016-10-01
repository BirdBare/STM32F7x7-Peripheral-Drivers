//
//
//
//
//

#include "stm32f7xx.h"
#include "STM32F767_GPIO.h"
#include "STM32F767_SYSTICK.h"

int main(void)
{

  //Init Code

  SysTick_EnableTimer();
  GPIO_EnableClock(GPIO_CLOCK_GPIOB);


  uint32_t f=0;

  f = GPIO_PIN_14;

  GPIO_SetPins(GPIOB, f, GPIO_MODE_OUTPUT, GPIO_OUTTYPE_PUSHPULL,
    GPIO_OUTSPEED_VHIGH, GPIO_PUPD_OFF, GPIO_NO_USE);


uint32_t count = 0;

loop:

 // Microcontroller Repeat Code


DelayMilli(100);
GPIO_ToggleOutput(GPIOB,f);

goto loop;


  return 1;
}


