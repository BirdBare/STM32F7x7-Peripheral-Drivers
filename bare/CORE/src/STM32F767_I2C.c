//
//
//
//
//



#include "STM32F767_I2C.h"
#include "STM32F767_RCC.h"
#include "STM32F767_PERIPH.h"

struct I2Cxo
	I2C1o = {&RCC->APB1ENR,21,0,0,I2C1},
	I2C2o = {&RCC->APB1ENR,22,0,0,I2C2},
	I2C3o = {&RCC->APB1ENR,23,0,0,I2C3},
	I2C4o = {&RCC->APB1ENR,24,0,0,I2C4};

//******************************************************************************
//	
//										 
//	
//******************************************************************************
int I2C_Config(struct I2Cxo *I2Co, int CR1, int OAR1, int OAR2, int TIMINGR, 
	int TIMEOUTR)
{
	volatile I2C_TypeDef * const I2Cx = I2Co->I2Cx;
	
	if((I2Cx->CR1 & I2C_CR1_PE) == 0)
	{
		I2Cx->CR1 = CR1;
		I2Cx->OAR1 = OAR1;
		I2Cx->OAR2 = OAR2;
		I2Cx->TIMINGR = TIMINGR;
		I2Cx->TIMEOUTR = TIMEOUTR;
	
		return 0;
	}
	return I2C_CONFIG_ENABLED;
}

//******************************************************************************
//	
//										 
//	
//******************************************************************************
int I2C_ResetConfig(struct I2Cxo *I2Co)
{
	if((I2Co->I2Cx->CR1 & I2C_CR1_PE) == 0)
	{
		RCC_Reset((struct RCCxo *)I2Co);

		return 0;
	}

	return I2C_CONFIG_ENABLED;
}

//******************************************************************************
//	
//										 
//	
//******************************************************************************
int I2C_Enable(struct I2Cxo *I2Co)
{
	I2Co->I2Cx->CR1 |= I2C_CR1_PE;
	
	return 0;
}

//******************************************************************************
//	
//										 
//	
//******************************************************************************
int I2C_Disable(struct I2Cxo *I2Co)
{	
	volatile I2C_TypeDef * const I2Cx = I2Co->I2Cx;
	
	if((I2Cx->ISR & I2C_ISR_STOPF) != 0)
	{
		I2Cx->CR1 &= ~I2C_CR1_PE;
		
		return 0;
	}
	return I2C_DISABLE_TRANSFER;
}



#define I2C_ICR_MASK 0b11111100111000

//******************************************************************************
//	
//										 
//	
//******************************************************************************
int I2C_StartMaster(struct I2Cxo *I2Co, int CR2)
{	
	volatile I2C_TypeDef * const I2Cx = I2Co->I2Cx;

	I2Cx->ICR = I2C_ICR_MASK;
	//reset all flags

	I2Cx->CR2 = CR2 | I2C_CR2_START;

	PERIPH_WaitTillReset(&I2Cx->CR2, I2C_CR2_START);

	if(PERIPH_GetStatus(&I2Cx->ISR, I2C_ISR_NACKF) != 0)
	{
		I2Cx->ICR = I2C_ICR_NACKCF;

		return I2C_START_NACK;
	}
	
	return 0;
}


















