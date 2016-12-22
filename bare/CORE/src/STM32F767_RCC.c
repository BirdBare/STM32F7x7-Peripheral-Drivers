//
//
//
//
//


#include "STM32F767_RCC.h"

//******************************************************************************
//	
//										 
//	
//******************************************************************************
uint32_t RCC_EnableClock(struct RCCxo *RCCo)
{
	uint32_t setbit = 1 << RCCo->clockbitoffset;
	uint32_t prevstate = *RCCo->clockreg & setbit;

	*RCCo->clockreg |= setbit;
	
	return prevstate;
}

//******************************************************************************
//	
//										 
//	
//******************************************************************************
uint32_t RCC_DisableClock(struct RCCxo *RCCo)
{
	uint32_t resetbit = 1 << RCCo->clockbitoffset;
	uint32_t prevstate = *RCCo->clockreg & resetbit;

	*RCCo->clockreg &= ~resetbit;
	
	return !prevstate;
}

void RCC_Reset(struct RCCxo *RCCo)
{
	uint32_t bit = 1 << RCCo->clockbitoffset;

	uint32_t *resetreg = (void*)((uint32_t)RCCo->clockreg -0x20);

	*resetreg |= bit;
	for(int i = 10; i != 0; i--)
	{
		asm volatile("");
	}
	//wait for 35 ish clock cycles to let things reset before turning proceding.

	*resetreg &= ~bit;
}








