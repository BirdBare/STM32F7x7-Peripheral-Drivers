


#ifndef STM32F767_USART_H
#define STM32F767_USART_H

#include "stm32f7xx.h"
#include "BARE_DEFINES.h"
//#include "STM32F767_xxx.h"

struct USARTxo
{
	volatile uint32_t  * const clockreg;
	const uint8_t clockbitoffset;
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


#define USART_CONFIG_ENABLED 1


//******************************************************************************
//	
//										 
//	
//******************************************************************************
uint32_t USART_Config(struct USARTxo *USARTo, uint32_t CR1, uint32_t CR2, 
	uint32_t CR3, uint32_t BRR, uint32_t GTPR, uint32_t RTOR);

//******************************************************************************
//	
//										 
//	
//******************************************************************************
uint32_t USART_ResetConfig(struct USARTxo *USARTo);

//******************************************************************************
//	
//										 
//	
//******************************************************************************
uint32_t USART_Enable(struct USARTxo *USARTo);

//******************************************************************************
//	
//										 
//	
//******************************************************************************
uint32_t USART_Disable(struct USARTxo *USARTo);


//******************************************************************************
//	
//										 
//	
//******************************************************************************
ALWAYS_INLINE uint32_t USART_Get8(struct USARTxo *USARTo)
{
	uint32_t ret;
	ASM(" ldrb %0, [%1, #0x24]" :"=r" (ret) : "r" (USARTo->USARTx));
	return ret;
}

//******************************************************************************
//	
//										 
//	
//******************************************************************************
ALWAYS_INLINE void USART_Put8(struct USARTxo *USARTo, uint32_t Data)
{
	ASM(" strb %1, [%0, #0x28]" ::"r" (USARTo->USARTx), "r" (Data));
}
#endif
