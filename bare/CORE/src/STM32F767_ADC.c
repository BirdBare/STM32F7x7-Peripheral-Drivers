//
//
//
//
//



#include "STM32F767_ADC.h"
#include "STM32F767_RCC.h"

struct ADCxo
	ADC1o = {&RCC->APB2ENR,8,0,0,ADC1},
	ADC2o = {&RCC->APB2ENR,9,0,0,ADC2},
	ADC3o = {&RCC->APB2ENR,10,0,0,ADC3};


int ADC_Config(struct ADCxo *ADCo, int CR1, int CR2, int HTR, int LTR)
{
	volatile ADC_TypeDef * const ADCx = ADCo->ADCx;

	if((ADCx->CR2 & ADC_CR2_ADON) == 0)
	{
		ADCx->CR1 = CR1;
		ADCx->HTR = HTR;
		ADCx->LTR = LTR;
		ADCx->CR2 = CR2;

		return 0;
	}
	return ADC_CONFIG_ENABLED;
}



int ADC_ConfigRegular(struct ADCxo *ADCo, int SeqHigh, int SeqMid, 
	int SeqLow, int SampHigh, int SampLow)
{
	volatile ADC_TypeDef * const ADCx = ADCo->ADCx;

	if((ADCx->CR2 & ADC_CR2_ADON) == 0)
	{
		ADCx->SQR1 = SeqHigh;
		ADCx->SQR2 = SeqMid;
		ADCx->SQR3 = SeqLow;
		ADCx->SMPR1 = SampHigh;
		ADCx->SMPR2 = SampLow;

		return 0;
	}
	return ADC_CONFIG_ENABLED;
}



int ADC_ConfigInjected(struct ADCxo *ADCo, int JSQR, int JOFR1, 
	int JOFR2, int JOFR3, int JOFR4)
{
	volatile ADC_TypeDef * const ADCx = ADCo->ADCx;

	if((ADCx->CR2 & ADC_CR2_ADON) == 0)
	{
		ADCx->CR2 = JSQR;
		ADCx->JOFR1 = JOFR1;
		ADCx->JOFR2 = JOFR2;
		ADCx->JOFR3 = JOFR3;
		ADCx->JOFR4 = JOFR4;

		return 0;
	}
	return ADC_CONFIG_ENABLED;
}




int ADC_ResetConfig(struct ADCxo *ADCo)
{
	volatile ADC_TypeDef * const ADCx = ADCo->ADCx;

	if((ADCx->CR2 & ADC_CR2_ADON) == 0)
	{
		RCC_Reset((struct RCCxo *)ADCo);

		return 0;
	}
	return ADC_CONFIG_ENABLED;
}

int ADC_Enable(struct ADCxo *ADCo)
{
	ADCo->ADCx->CR2 |= ADC_CR2_ADON;
	return 0;
}

int ADC_Disable(struct ADCxo *ADCo)
{	
	ADCo->ADCx->CR2 &= ~ADC_CR2_ADON;
	return 0;
}

int ADC_StartRegular(struct ADCxo *ADCo)
{
	volatile ADC_TypeDef * const ADCx = ADCo->ADCx;

	if((ADCx->CR2 & ADC_CR2_ADON) != 0)
	{
		ADCx->CR2 |= ADC_CR2_SWSTART;
		
		return 0;
	}
	return ADC_START_ADON;
}

int ADC_StartInjected(struct ADCxo *ADCo)
{
	volatile ADC_TypeDef * const ADCx = ADCo->ADCx;

	if((ADCx->CR2 & ADC_CR2_ADON) != 0)
	{
		ADCx->CR2 |= ADC_CR2_JSWSTART;
		
		return 0;
	}
	return ADC_START_ADON;
}

int ADC_Get16(struct ADCxo *ADCo)
{
	uint32_t ret;
	ASM(" ldrh %0, [%1, #0x4c]" : "=r" (ret) : "r" (ADCo->ADCx));
	return ret;
}
int ADC_Get16_1(struct ADCxo *ADCo)
{
	uint32_t ret;
	ASM(" ldrh %0, [%1, #0x3c]" : "=r" (ret) : "r" (ADCo->ADCx));
	return ret;
}
int ADC_Get16_2(struct ADCxo *ADCo)
{
	uint32_t ret;
	ASM(" ldrh %0, [%1, #0x40]" : "=r" (ret) : "r" (ADCo->ADCx));
	return ret;
}
int ADC_Get16_3(struct ADCxo *ADCo)
{
	uint32_t ret;
	ASM(" ldrh %0, [%1, #0x44]" : "=r" (ret) : "r" (ADCo->ADCx));
	return ret;
}
int ADC_Get16_4(struct ADCxo *ADCo)
{
	uint32_t ret;
	ASM(" ldrh %0, [%1, #0x48]" : "=r" (ret) : "r" (ADCo->ADCx));
	return ret;
}







