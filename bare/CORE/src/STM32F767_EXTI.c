//
//
//
//
//



#ifndef STM32F767_EXTI_H
#define STM32F767_EXTI_H

#include "stm32f767xx.h"
//#include "STM32F767_.h"

int EXTI_ConfigEnable(int EXTI_BIT, int IMR, int EMR, int RTSR, int FTSR)
{

	uint32_t setpins = EXTI_BIT & (EXTI->EMR | EXTI->IMR);

	if(setpins == EXTI_BIT)
	{
		EXTI->IMR |= IMR;
		EXTI->EMR |= EMR;
		EXTI->RTSR = (EXTI->RTSR & ~EXTI_BIT) | RTSR;
		EXTI->FTSR = (EXTI->FTSR & ~EXTI_BIT) | FTSR;
	}

	return setpins; 
}

void EXTI_Disable(int EXTI_BIT)
{
	EXTI->IMR &= ~EXTI_BIT;
	EXTI->EMR &= ~EXTI_BIT;
}








#endif
