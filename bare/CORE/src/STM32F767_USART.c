//
//
//
//
//




#include "STM32F767_USART.h"

const struct USARTxo
	USART1o = {&RCC->APB2ENR,USART1_CLOCK_OFFSET,0,0,0,USART1},
	USART2o = {&RCC->APB1ENR,USART2_CLOCK_OFFSET,0,0,0,USART2},
	USART3o = {&RCC->APB1ENR,USART3_CLOCK_OFFSET,0,0,0,USART3},
	USART4o = {&RCC->APB1ENR,UART4_CLOCK_OFFSET,0,0,0,UART4},
	USART5o = {&RCC->APB1ENR,UART5_CLOCK_OFFSET,0,0,0,UART5},
	USART6o = {&RCC->APB2ENR,USART6_CLOCK_OFFSET,0,0,0,USART6},
	USART7o = {&RCC->APB1ENR,UART7_CLOCK_OFFSET,0,0,0,UART7},
	USART8o = {&RCC->APB1ENR,UART8_CLOCK_OFFSET,0,0,0,UART8};

uint32_t USART_EnableClock(uint32_t USART_CLOCK)
{
	uint32_t *RCCx = 0;

	switch((uint32_t)USART_CLOCK)
	{
		case (uint32_t)USART_CLOCK_USART1:
		case (uint32_t)USART_CLOCK_USART6:
			RCCx = &RCC->APB2ENR;
		break;

		case (uint32_t)USART_CLOCK_USART2:
		case (uint32_t)USART_CLOCK_USART3:
		case (uint32_t)USART_CLOCK_UART4:
		case (uint32_t)USART_CLOCK_UART5:
		case (uint32_t)USART_CLOCK_UART7:
		case (uint32_t)USART_CLOCK_UART8:
			RCCx = &RCC->APB1ENR;
		break;
	};
	//get correct register to set

	uint32_t rccreg = *RCCx;
	//get reg value to check if clock is already set

	if((rccreg & USART_CLOCK) == 0)
	{
		*RCCx = rccreg | USART_CLOCK;
		return 0;
	}
	return USART_CLOCK_ENABLED; 
}


