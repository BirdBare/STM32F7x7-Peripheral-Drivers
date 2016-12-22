//
//
//
//
//



#include "STM32F767_RNG.h"
#include "STM32F767_RCC.h"

struct RNGxo
	RNGo = {&RCC->AHB2ENR,6,0,0,RNG};

int RNG_Config(struct RNGxo *RNGo, int CR)
{
	volatile RNG_TypeDef * const RNGx = RNGo->RNGx;

	if((RNGx->CR & RNG_CR_RNGEN) == 0)
	{
		RNGx->CR = CR;

		return 0;
	}
	return RNG_CONFIG_ENABLED;
}

int RNG_ResetConfig(struct RNGxo *RNGo)
{
	
	if((RNGo->RNGx->CR & RNG_CR_RNGEN) == 0)
	{
		RCC_Reset((struct RCCxo *)RNGo);

		return 0;
	}
	return RNG_CONFIG_ENABLED;
}


int RNG_Enable(struct RNGxo *RNGo)
{
	RNGo->RNGx->CR |= RNG_CR_RNGEN;
	return 0;
}

int RNG_Disable(struct RNGxo *RNGo)
{
	RNGo->RNGx->CR &= ~RNG_CR_RNGEN;
	return 0;
}





