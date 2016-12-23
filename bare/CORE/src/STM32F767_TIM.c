//
//
//
//
//



#include "STM32F767_TIM.h"
#include "STM32F767_RCC.h"

struct TIMxo
	TIM1o = {&RCC->APB2ENR,0,0,0,TIM1},
	TIM2o = {&RCC->APB1ENR,0,0,0,TIM2},
	TIM3o = {&RCC->APB1ENR,1,0,0,TIM3},
	TIM4o = {&RCC->APB1ENR,2,0,0,TIM4},
	TIM5o = {&RCC->APB1ENR,3,0,0,TIM5},
	TIM6o = {&RCC->APB1ENR,4,0,0,TIM6},
	TIM7o = {&RCC->APB1ENR,5,0,0,TIM7},
	TIM8o = {&RCC->APB2ENR,1,0,0,TIM8},
	TIM9o = {&RCC->APB2ENR,16,0,0,TIM9},
	TIM10o = {&RCC->APB2ENR,17,0,0,TIM10},
	TIM11o = {&RCC->APB2ENR,18,0,0,TIM11},
	TIM12o = {&RCC->APB1ENR,6,0,0,TIM12},
	TIM13o = {&RCC->APB1ENR,7,0,0,TIM13},
	TIM14o = {&RCC->APB1ENR,8,0,0,TIM14};


int TIM_Config(struct TIMxo *TIMo, int CR1, int CR2, int SMCR, int DIER, 
	int PSC, int ARR)
{
	volatile TIM_TypeDef * const TIMx = TIMo->TIMx;

	if((TIMx->CR1 & TIM_CR1_CEN) == 0)
	{
		TIMx->ARR = ARR;
		TIMx->PSC = PSC;
		TIMx->DIER = (TIMx->DIER & ~0b0100000111000001) | DIER;
		TIMx->SMCR = SMCR;
		TIMx->CR2 = CR2;
		TIMx->CR1 = CR1;

		return 0;
	}
	return TIM_CONFIG_ENABLED;
}


int TIM_ConfigChannel(struct TIMxo *TIMo, int Channel, int DIER, int CCMR, 
	int CCER)
{
	volatile TIM_TypeDef * const TIMx = TIMo->TIMx;

	if((TIMx->CCER & TIM_CCER_CC1E) == 0)
	{
		TIMx->DIER = (TIMx->DIER & ~(0b0000001000000010 << Channel)) 
			| (DIER << Channel);

		Channel--;

		TIMx->CCER = ((TIMx->CCER & ~(0b0000000000001111 << (Channel << 2))) 
			| (CCER << (Channel << 2)));

		uint32_t temp = (Channel & 1) << 3;
		//get bits offset from channel

		CCMR <<= temp;
		//shift CCMR to correct position for channel

		temp = ~(0b10000000011111111 << temp);
		//create bit mask for CCMR reg

		__IO uint32_t *CCMRreg = &TIMx->CCMR1;
		//get CCMR1

		switch(Channel >> 1)
		{
			case 2:
				CCMRreg = (void *)((uint32_t)CCMRreg + 0x38);
				//get to CCMR3

			case 1:
				CCMRreg = (void *)((uint32_t)CCMRreg + 0x4);				
				//get to CCMR2
		}
		
		*CCMRreg |= (*CCMRreg & temp) | CCMR;

		return 0;
	}
	return TIM_CONFIG_ENABLED;
}

int TIM_ResetConfig(struct TIMxo *TIMo)
{
	if((TIMo->TIMx->CR1 & TIM_CR1_CEN) == 0)
	{
		RCC_Reset(&TIMo);
		return 0;
	}
	return TIM_CONFIG_ENABLED;
}

void TIM_Enable(struct TIMxo *TIMo)
{
	TIMo->TIMx->CR1 |= TIM_CR1_CEN;
}

void TIM_EnableChannel(struct TIMxo *TIMo, int Channel)
{
	TIMo->TIMx->CCER |= TIM_CCER_CC1E << ((Channel - 1) << 2);
}

void TIM_Disable(struct TIMxo *TIMo)
{
	TIMo->TIMx->CR1 &= ~TIM_CR1_CEN;
}

void TIM_DisableChannel(struct TIMxo *TIMo, int Channel)
{
	TIMo->TIMx->CCER &= ~(TIM_CCER_CC1E << ((Channel - 1) << 2));
}

void TIM_Get32(struct TIMxo *TIMo, int DataArray[6])
{
	volatile TIM_TypeDef * const TIMx = TIMo->TIMx;

	DataArray[0] = TIMx->CCR1;
	DataArray[1] = TIMx->CCR2;
	DataArray[2] = TIMx->CCR3;
	DataArray[3] = TIMx->CCR4;
	DataArray[4] = TIMx->CCR5;
	DataArray[5] = TIMx->CCR6;
}




