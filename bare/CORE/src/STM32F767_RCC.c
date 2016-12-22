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
uint32_t RCC_EnableClock(structxo *RCCo)
{
	uint32_t setbit = 1 << ((struct RCCxo *)RCCo)->clockbitoffset;
	uint32_t prevstate = *((struct RCCxo *)RCCo)->clockreg & setbit;

	*((struct RCCxo *)RCCo)->clockreg |= setbit;
	
	return prevstate;
}

//******************************************************************************
//	
//										 
//	
//******************************************************************************
uint32_t RCC_DisableClock(structxo *RCCo)
{
	uint32_t resetbit = 1 << ((struct RCCxo *)RCCo)->clockbitoffset;
	uint32_t prevstate = *((struct RCCxo *)RCCo)->clockreg & resetbit;

	*((struct RCCxo *)RCCo)->clockreg &= ~resetbit;
	
	return !prevstate;
}

void RCC_Reset(structxo *RCCo)
{
	uint32_t bit = 1 << ((struct RCCxo *)RCCo)->clockbitoffset;

	uint32_t *resetreg = 
		(void*)((uint32_t)((struct RCCxo *)RCCo)->clockreg -0x20);

	*resetreg |= bit;
	for(int i = 10; i != 0; i--)
	{
		asm volatile("");
	}
	//wait for 35 ish clock cycles to let things reset before turning proceding.

	*resetreg &= ~bit;
}








