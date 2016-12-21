//
//
//
//
//



#ifndef STM32F767_USART_H
#define STM32F767_USART_H

#include "stm32f7xx.h"
#include "BARE_DEFINES.h"
#include "STM32F767_RCC.h"
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


ALWAYS_INLINE uint32_t USART_Config(struct USARTxo *USARTo, uint32_t CR1, 
	uint32_t CR2, uint32_t CR3, uint32_t BRR)
{
	volatile USART_TypeDef * const USARTx = USARTo->USARTx;

	uint32_t prevstate = USARTx->CR1 & USART_CR1_UE;

	USARTx->CR2 = CR2;
	USARTx->CR3 = CR3;
	USARTx->BRR = BRR;
	USARTx->CR1 = CR1;

	return prevstate;
}


ALWAYS_INLINE uint32_t USART_ResetConfig(struct USARTxo *USARTo)
{
	uint32_t prevstate = USARTo->USARTx->CR1 & USART_CR1_UE;

	RCC_DisableClock((struct RCCo *)USARTo);
	RCC_EnableClock((struct RCCo *)USARTo);

	return prevstate;
}









#endif
