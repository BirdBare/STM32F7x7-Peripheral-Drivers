//
//
//
//
//



#ifndef STM32F767_PWR_H
#define STM32F767_PWR_H

#include "stm32f767xx.h"
//#include "STM32F767_.h"

struct PWRxo
{
	volatile uint32_t * const clockreg;
	const uint8_t clockbitoffset;
	uint8_t unused1;
	uint16_t unused2;

	volatile PWR_TypeDef * const PWRx;
};

extern struct PWRxo
	PWRo;

void PWR_Config(struct PWRxo *PWRo, int CR1, int CR2, int CSR2);

#define PWR_ENABLE_CLOCK 1
int PWR_EnableOverdrive(struct PWRxo *PWRo);


int PWR_DisableOverdrive(struct PWRxo *PWRo);








#endif
