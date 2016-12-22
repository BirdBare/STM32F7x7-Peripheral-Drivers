//
//
//
//
//



#ifndef STM32F767_TIM_H
#define STM32F767_TIM_H

#include "stm32f767xx.h"
//#include "STM32F767_.h"

struct TIMxo
{
	volatile uint32_t * const clockreg;
	const uint8_t clockbitoffset;
	uint8_t unused1;
	uint16_t unused2;

	volatile TIM_TypeDef * const TIMx;
};

extern struct TIMxo
	TIM1o,
	TIM2o,
	TIM3o,
	TIM4o,
	TIM5o,
	TIM6o,
	TIM7o,
	TIM8o,
	TIM9o,
	TIM10o,
	TIM11o,
	TIM12o,
	TIM13o,
	TIM14o;

#define TIM_CONFIG_ENABLED 1
int TIM_Config(struct TIMxo *TIMo, int CR1, int CR2, int SMCR, int DIER, 
	int PSC, int ARR);

int TIM_ConfigChannel(struct TIMxo *TIMo, int Channel, int DIER, int CCMR, 
	int CCER);

int TIM_ResetConfig(struct TIMxo *TIMo);

int TIM_Enable(struct TIMxo *TIMo);

int TIM_EnableChannel(struct TIMxo *TIMo, int Channel);

int TIM_Disable(struct TIMxo *TIMo);

int TIM_DisableChannel(struct TIMxo *TIMo, int Channel);

void TIM_Get32(struct TIMxo *TIMo, int DataArray[6]);


#endif
