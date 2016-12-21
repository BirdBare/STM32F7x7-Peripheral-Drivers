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
	uint32_t setbit = 1 << RCCo->clockregoffset;
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
	uint32_t resetbit = 1 << RCCo->clockregoffset;
	uint32_t prevstate = *RCCo->clockreg & resetbit;

	*(uint32_t *)((uint32_t)RCCo->clockreg - 0x20) = resetbit;
	
	return !prevstate;
}



