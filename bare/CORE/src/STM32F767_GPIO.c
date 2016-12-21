//
//
//
//
//

#include "STM32F767_GPIO.h"

uint32_t GPIO_EnableClock(uint32_t GPIO_CLOCK)
{
	uint32_t prevstate = !!(RCC->AHB1ENR & GPIO_CLOCK);
	RCC->AHB1ENR |= (GPIO_CLOCK);
	return prevstate;
}

uint32_t GPIO_DisabeClock(uint32_t GPIO_CLOCK) 
{
	if(GPIO_PINS[GPIO_CLOCK] == 0)
	{
		RCC->AHB1RSTR |= (GPIO_CLOCK);
		return 0;
	}
	return GPIO_ERROR_CLOCK_PINS;
}



uint16_t GPIO_PINS [11] = {0};


uint32_t GPIO_SetPins(GPIO_TypeDef *GPIOx,
  const uint32_t GPIO_PIN,const uint32_t GPIO_MODE, 
  const uint32_t GPIO_OUTTYPE, const uint32_t GPIO_OUTSPEED, 
  const uint32_t GPIO_PUPD,const uint32_t GPIO_ALTFUNCTION)
{
	uint32_t index = GPIO_INDEX(GPIOx), respins = ~GPIO_PINS[index],
		setpins = 0;

	uint32_t MODE = 0, TYPE = 0, SPEED = 0, PUPD = 0;

  for(uint8_t count = 0; count < 16; count++)
  {
    if((GPIO_PIN & ((uint32_t)0b1 << count) & respins) != 0)
    {
      uint32_t count2 = count << 1;

			//indicates used or reserved pins. will be stored and returned.
			setpins |= ((uint32_t)0b1 << count);
    
      MODE |= (GPIO_MODE << (count2)); 
      //
      TYPE |= (GPIO_OUTTYPE << count);
      //      
      SPEED |= (GPIO_OUTSPEED << (count2)); 
      //
      PUPD |= (GPIO_PUPD << (count2)); 
      //  
      
      count2 = (count & 0b111) << 2;
			//
      GPIOx->AFR[count >> 3] &= ~((uint32_t)0b1111 << ((count2))); 
      //Sets Pin Alternate Function to reset GPIO
      
      GPIOx->AFR[count >> 3] |= (GPIO_ALTFUNCTION << ((count2)));
      //Sets Pin Alternate Function
    }
  }
	GPIOx->MODER &= ~MODE;
	GPIOx->OTYPER &= ~TYPE;
	GPIOx->OSPEEDR &= ~SPEED;
	GPIOx->PUPDR &= ~PUPD;

	GPIOx->MODER |= MODE;
	GPIOx->OTYPER |= TYPE;
	GPIOx->OSPEEDR |= SPEED;
	GPIOx->PUPDR |= PUPD;

	GPIO_PINS[index] |= setpins;

	return setpins;
}

/*
extern void GPIO_SetOutput(GPIO_TypeDef *GPIO_PORT,uint32_t GPIO_PIN);

extern void GPIO_ResetOutput(GPIO_TypeDef *GPIO_PORT,uint32_t GPIO_PIN);

extern void GPIO_ChangeOutput(GPIO_TypeDef *GPIOx,uint32_t setGPIO_PIN,uint32_t resetGPIO_PIN);

extern void GPIO_ToggleOutput(GPIO_TypeDef *GPIO_PORT,uint32_t GPIO_PIN);

extern uint32_t GPIO_GetInState(GPIO_TypeDef *GPIO_PORT,uint32_t GPIO_PIN);

extern uint32_t GPIO_GetOutState(GPIO_TypeDef *GPIO_PORT,uint32_t GPIO_PIN); 
*/
