//
//
//
//
//



#ifndef STM32F767_LPTIM_H
#define STM32F767_LPTIM_H

#include "stm32f767xx.h"
//#include "STM32F767_.h"

struct LPTIMxo
{
	volatile uint32_t * const clockreg;
	const uint8_t clockbitoffset;
	uint8_t unused1;
	uint16_t unused2;

	volatile LPTIM_TypeDef * const LPTIMx;
};

extern struct LPTIMxo
	LPTIM1o;

#define LPTIM_CONFIG_ENABLED 1
int LPTIM_Config(struct LPTIMxo * LPTIMo, int IER, int CFGR);


int LPTIM_ResetConfig(struct LPTIMxo * LPTIMo);


void LPTIM_Enable(struct LPTIMxo * LPTIMo);


void LPTIM_Disable(struct LPTIMxo * LPTIMo);


void LPTIM_StartSingle(struct LPTIMxo * LPTIMo);


void LPTIM_StartContinuous(struct LPTIMxo * LPTIMo);







#endif
