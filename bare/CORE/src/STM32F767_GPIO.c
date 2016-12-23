//
//
//
//
//

#include "STM32F767_GPIO.h"

struct GPIOxo
	GPIOAo = {&RCC->AHB1ENR,0,0,0,GPIOA},
	GPIOBo = {&RCC->AHB1ENR,1,0,0,GPIOB},
	GPIOCo = {&RCC->AHB1ENR,2,0,0,GPIOC},
	GPIODo = {&RCC->AHB1ENR,3,0,0,GPIOD},
	GPIOEo = {&RCC->AHB1ENR,4,0,0,GPIOE},
	GPIOFo = {&RCC->AHB1ENR,5,0,0,GPIOF},
	GPIOGo = {&RCC->AHB1ENR,6,0,0,GPIOG},
	GPIOHo = {&RCC->AHB1ENR,7,0,0,GPIOH},
	GPIOIo = {&RCC->AHB1ENR,8,0,0,GPIOI},
	GPIOJo = {&RCC->AHB1ENR,9,0,0,GPIOJ},
	GPIOKo = {&RCC->AHB1ENR,10,0,0,GPIOK};

//******************************************************************************
//	
//									GPIO_ConFig
//		return: 0		- Success
//						!0	- Fail -- Pins not set returned
//	
//******************************************************************************
uint32_t GPIO_Config(volatile struct GPIOxo * const GPIOo, uint32_t GPIO_PIN,
	const uint32_t GPIO_MODE, const uint32_t GPIO_OUTTYPE, 
	const uint32_t GPIO_OUTSPEED, const uint32_t GPIO_PUPD,
	const uint32_t GPIO_ALTFUNCTION)
{

	volatile GPIO_TypeDef * const GPIOx = GPIOo->GPIOx;

	uint32_t respins = ~GPIOo->used, setpins = 0, setpins2 = 0;
	//get old usedpins

	GPIOo->used |= GPIO_PIN;
	//update usedpins

	uint32_t MODE = 0, TYPE = 0, SPEED = 0, PUPD = 0;

  for(uint8_t count = 0; count < 16; count++)
  {
    if((GPIO_PIN & ((uint32_t)0b1 << count) & respins) != 0)
    {
      uint32_t count2 = count << 1;

			//indicates used or reserved pins. will be stored and returned.
			setpins |= ((uint32_t)0b1 << count);
			setpins2 |= ((uint32_t)0b11 << count2);
    
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
      GPIOx->AFR[count >> 3] &= ~(0b1111 << ((count2)));
      GPIOx->AFR[count >> 3] |= (GPIO_ALTFUNCTION << ((count2)));
      //Sets Pin Alternate Function
    }
  }
	GPIOx->MODER &= ~setpins2;
	GPIOx->OTYPER &= ~setpins;
	GPIOx->OSPEEDR &= ~setpins2;
	GPIOx->PUPDR &= ~setpins2;

	GPIOx->MODER |= MODE;
	GPIOx->OTYPER |= TYPE;
	GPIOx->OSPEEDR |= SPEED;
	GPIOx->PUPDR |= PUPD;

	return setpins;
}


