//
//
//
//
//



#ifndef STM32F767_SYSCFG_H
#define STM32F767_SYSCFG_H

#include "stm32f767xx.h"
//#include "STM32F767_.h"

struct SYSCFGxo
{
	volatile uint32_t * const clockreg;
	const uint8_t clockbitoffset;
	uint8_t unused1;
	uint16_t unused2;

	volatile SYSCFG_TypeDef * const SYSCFGx;
};

struct SYSCFGxo
	SYSCFGo = {&RCC->APB2ENR,14,0,0,SYSCFG};

void SYSCFG_Config(struct SYSCFGxo *SYSCFGo, int MEMRMP, int CBR, int CMPCR)
{
	SYSCFG->MEMRMP = MEMRMP;
	SYSCFG->CBR = CBR;
	SYSCFG->CMPCR = CMPCR;
}


void SYSCFG_ConfigEXTI(struct SYSCFGxo *SYSCFGo, int EXTIHigh, int EXTIMidHigh, 
	int EXTIMidLow, int EXTILow)
{
	SYSCFG->EXTICR[3] = EXTIHigh;	
	SYSCFG->EXTICR[2] = EXTIMidHigh;	
	SYSCFG->EXTICR[1] = EXTIMidLow;	
	SYSCFG->EXTICR[0] = EXTILow;	
}




#endif
