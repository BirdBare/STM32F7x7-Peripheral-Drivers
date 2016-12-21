//
//
//
//
//



#ifndef STM32F767_RCC_H
#define STM32F767_RCC_H

#include "BARE_STM32F767.h"

#define RCC_CLOCK_ENABLED 1

//Object struct of the Reset and clock control. Every object who contains
// a clock must contain this in the structure first. This will allow us to
// enable the clock from the object.

struct RCCxo
{
	volatile uint32_t * const clockreg;			//register where clock enable bit is.
	const uint8_t clockregoffset; //offset to the clock enable bit.
	uint8_t unused1;
	uint8_t unused2;
	uint8_t unused3;
};

//******************************************************************************
//	
//										 
//	
//******************************************************************************
uint32_t RCC_EnableClock(struct RCCxo *RCCo);

//******************************************************************************
//	
//										 
//	
//******************************************************************************
uint32_t RCC_DisableClock(struct RCCxo *RCCo);

#define RCC_EnableClockAHB1(AHB1_CLOCK_x) \
	RCC->AHB1ENR |= AHB1_CLOCK_x
#define RCC_EnableClockAHB2(AHB2_CLOCK_x) \
	RCC->AHB2ENR |= AHB2_CLOCK_x
#define RCC_EnableClockAPB1(APB1_CLOCK_x) \
	RCC->APB1ENR |= APB1_CLOCK_x
#define RCC_EnableClockAPB2(APB2_CLOCK_x) \
	RCC->APB2ENR |= APB2_CLOCK_x

#define RCC_DisableClockAHB1(AHB1_CLOCK_x) \
	RCC->AHB1RSTR &= ~AHB1_CLOCK_x
#define RCC_DisableClockAHB2(AHB2_CLOCK_x) \
	RCC->AHB2RSTR &= ~AHB2_CLOCK_x
#define RCC_DisableClockAPB1(APB1_CLOCK_x) \
	RCC->APB1RSTR &= ~APB1_CLOCK_x
#define RCC_DisableClockAPB2(APB2_CLOCK_x) \
	RCC->APB2RSTR &= ~APB2_CLOCK_x



#endif
