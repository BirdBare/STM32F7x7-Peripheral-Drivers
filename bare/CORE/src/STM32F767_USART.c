//
//
//
//
//





#include "STM32F767_USART.h"
#include "STM32F767_GPIO.h"

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
		RCC_DisableClock((struct RCCxo *)USARTo);
		RCC_EnableClock((struct RCCxo *)USARTo);
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
	volatile USART_TypeDef * const USARTx = USARTo->USARTx;
	//get USARTx

	volatile struct GPIOxo * const GPIOo = USARTo->GPIOo;
	//get GPIOo

	uint32_t pins = USARTo->pins, afr = USARTo->afr;
	//get pins, afr

	if(GPIOo != 0 && pins != 0 && afr != 0xff)
	{
		if((USARTx->CR1 & USART_CR1_UE) == 0)
		{	
			RCC_EnableClock((struct RCCxo *)GPIOo);
			//Enable GPIO clock

			uint32_t setpins = GPIO_Config(GPIOo, pins, GPIO_MODE_ALTERNATE, 
														GPIO_OUTTYPE_PUSHPULL, GPIO_OUTSPEED_VHIGH, 
														GPIO_PUPD_OFF, afr);
			//try to set the needed pins

			if(setpins == pins)
			{
				USARTx->CR1 |= USART_CR1_UE;
				//Enable USART

				return 0;
			}
			//check if Pins can be enabled

			GPIO_ResetConfig(GPIOo, setpins);
			RCC_DisableClock((struct RCCxo *)GPIOo);
			//Disable pins and clock

			return USART_ENABLE_PINS_USED;
		}
		//check if USART is not already enabled

		return USART_ENABLE_ENABLED;
	}
	//check if pin register values have been set


	return USART_ENABLE_PINS_UNSET;
}

//******************************************************************************
//	
//										 
//	
//******************************************************************************
uint32_t USART_Disable(struct USARTxo *USARTo)
{
	volatile USART_TypeDef * const USARTx = USARTo->USARTx;

	if((USARTx->CR1 & USART_CR1_UE) != 0)
	{
		//NEED TO FINISH



	}


	uint32_t prevstate = USARTx->CR1 & USART_CR1_UE;

	USARTx->CR1 &= ~USART_CR1_UE;

	return !prevstate;
}



