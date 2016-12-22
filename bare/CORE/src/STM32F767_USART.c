//
//
//
//
//





#include "STM32F767_USART.h"
#include "STM32F767_RCC.h"

struct USARTxo
	USART1o = {&RCC->APB2ENR,USART1_CLOCK_OFFSET,0xff,0,0,USART1},
	USART2o = {&RCC->APB1ENR,USART2_CLOCK_OFFSET,0xff,0,0,USART2},
	USART3o = {&RCC->APB1ENR,USART3_CLOCK_OFFSET,0xff,0,0,USART3},
	UART4o = {&RCC->APB1ENR,UART4_CLOCK_OFFSET,0xff,0,0,UART4},
	UART5o = {&RCC->APB1ENR,UART5_CLOCK_OFFSET,0xff,0,0,UART5},
	USART6o = {&RCC->APB2ENR,USART6_CLOCK_OFFSET,0xff,0,0,USART6},
	UART7o = {&RCC->APB1ENR,UART7_CLOCK_OFFSET,0xff,0,0,UART7},
	UART8o = {&RCC->APB1ENR,UART8_CLOCK_OFFSET,0xff,0,0,UART8};



//******************************************************************************
//	
//										 
//	
//******************************************************************************
uint32_t USART_Config(struct USARTxo *USARTo, uint32_t CR1, uint32_t CR2, 
	uint32_t CR3, uint32_t BRR, uint32_t GTPR, uint32_t RTOR)
{
	volatile USART_TypeDef * const USARTx = USARTo->USARTx;

	if((USARTx->CR1 & USART_CR1_UE) == 0)
	{
		USARTx->CR2 = CR2;
		USARTx->CR3 = CR3;
		USARTx->BRR = BRR;
		USARTx->GTPR = GTPR;
		USARTx->RTOR = RTOR;
		USARTx->CR1 = CR1;
		return 0;
	}
	return USART_CONFIG_ENABLED;
}

//******************************************************************************
//	
//										 
//	
//******************************************************************************
uint32_t USART_ResetConfig(struct USARTxo *USARTo)
{
	if((USARTo->USARTx->CR1 & USART_CR1_UE) == 0)
	{
		RCC_Reset((struct RCCxo *)USARTo);
		return 0;
	}
	return USART_CONFIG_ENABLED;
}

//******************************************************************************
//	
//										 
//	
//******************************************************************************
uint32_t USART_Enable(struct USARTxo *USARTo)
{
	USARTo->USARTx->CR1 |= USART_CR1_UE;

	return 0;
}

//******************************************************************************
//	
//										 
//	
//******************************************************************************
uint32_t USART_Disable(struct USARTxo *USARTo)
{	
	volatile USART_TypeDef * const USARTx = USARTo->USARTx;
	
	if((USARTx->ISR & USART_ISR_TC) != 0)
	{
		USARTo->USARTx->CR1 &= ~USART_CR1_UE;
		
		return 0;
	}
	return USART_DISABLE_TRANSFER;
}



