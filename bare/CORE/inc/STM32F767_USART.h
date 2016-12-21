//
//
//
//
//



#ifndef STM32F767_USART_H
#define STM32F767_USART_H

#include "stm32f7xx.h"
//#include "STM32F767_xxx.h"

#define USART_CLOCK_ENABLED 1

struct USARTxo
{
	volatile uint32_t  * const clockreg;
	const uint8_t clockregoffset;
	uint8_t unused1;
	uint8_t unused2;
	uint8_t unused3;

	volatile USART_TypeDef * const USARTx;
};

#define USART1_CLOCK_OFFSET 4
#define USART2_CLOCK_OFFSET 17
#define USART3_CLOCK_OFFSET 18
#define UART4_CLOCK_OFFSET 19
#define UART5_CLOCK_OFFSET 20
#define USART6_CLOCK_OFFSET 1
#define UART7_CLOCK_OFFSET 30
#define UART8_CLOCK_OFFSET 31

extern struct USARTxo
	USART1o, 
	USART2o,
	USART3o,
	UART4o,
	UART5o,
	USART6o,
	UART7o,
	UART8o;



#define USART_CLOCK_USART1 RCC_APB2ENR_USART1EN
#define USART_CLOCK_USART6 RCC_APB2ENR_USART6EN

#define USART_CLOCK_USART2 RCC_APB1ENR_USART2EN
#define USART_CLOCK_USART3 RCC_APB1ENR_USART3EN
#define USART_CLOCK_UART4 RCC_APB1ENR_UART4EN
#define USART_CLOCK_UART5 RCC_APB1ENR_UART5EN
#define USART_CLOCK_UART7 RCC_APB1ENR_UART7EN
#define USART_CLOCK_UART8 RCC_APB1ENR_UART8EN

extern uint32_t USART_EnableClock(uint32_t USART_CLOCK);
/*
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
}*/






#endif
