//
//
//
//
//



#ifndef STM32F767_USART_H
#define STM32F767_USART_H

#include "stm32f7xx.h"
#include "BARE_STM32F767.h"
//#include "STM32F767_xxx.h"


#define APB2_CLOCK_USART1 RCC_APB2ENR_USART1EN
#define APB2_CLOCK_USART6 RCC_APB2ENR_USART6EN

#define APB1_CLOCK_USART2 RCC_APB1ENR_USART2EN
#define APB1_CLOCK_USART3 RCC_APB1ENR_USART3EN
#define APB1_CLOCK_UART4 RCC_APB1ENR_UART4EN
#define APB1_CLOCK_UART5 RCC_APB1ENR_UART5EN
#define APB1_CLOCK_UART7 RCC_APB1ENR_UART7EN
#define APB1_CLOCK_UART8 RCC_APB1ENR_UART8EN








  //Register Functions
ALWAYS_INLINE void USART_SetCR1(USART_TypeDef *USARTx, uint32_t Data);
ALWAYS_INLINE uint32_t USART_GetCR1(USART_TypeDef *USARTx);
ALWAYS_INLINE void USART_SetBitsCR1(USART_TypeDef *USARTx, uint32_t Data);
ALWAYS_INLINE void USART_ResetBitsCR1(USART_TypeDef *USARTx, uint32_t Data);

ALWAYS_INLINE void USART_SetCR2(USART_TypeDef *USARTx, uint32_t Data);
ALWAYS_INLINE uint32_t USART_GetCR2(USART_TypeDef *USARTx);
ALWAYS_INLINE void USART_SetBitsCR2(USART_TypeDef *USARTx, uint32_t Data);
ALWAYS_INLINE void USART_ResetBitsCR2(USART_TypeDef *USARTx, uint32_t Data);

ALWAYS_INLINE void USART_SetCR3(USART_TypeDef *USARTx, uint32_t Data);
ALWAYS_INLINE uint32_t USART_GetCR3(USART_TypeDef *USARTx);
ALWAYS_INLINE void USART_SetBitsCR3(USART_TypeDef *USARTx, uint32_t Data);
ALWAYS_INLINE void USART_ResetBitsCR3(USART_TypeDef *USARTx, uint32_t Data);

ALWAYS_INLINE void USART_SetBRR(USART_TypeDef *USARTx, uint32_t Data);
ALWAYS_INLINE uint32_t USART_GetBRR(USART_TypeDef *USARTx);
ALWAYS_INLINE void USART_SetBitsBRR(USART_TypeDef *USARTx, uint32_t Data);
ALWAYS_INLINE void USART_ResetBitsBRR(USART_TypeDef *USARTx, uint32_t Data);

ALWAYS_INLINE void USART_SetGTPR(USART_TypeDef *USARTx, uint32_t Data);
ALWAYS_INLINE uint32_t USART_GetGTPR(USART_TypeDef *USARTx);
ALWAYS_INLINE void USART_SetBitsGTPR(USART_TypeDef *USARTx, uint32_t Data);
ALWAYS_INLINE void USART_ResetBitsGTPR(USART_TypeDef *USARTx, uint32_t Data);

ALWAYS_INLINE void USART_SetRTOR(USART_TypeDef *USARTx, uint32_t Data);
ALWAYS_INLINE uint32_t USART_GetRTOR(USART_TypeDef *USARTx);
ALWAYS_INLINE void USART_SetBitsRTOR(USART_TypeDef *USARTx, uint32_t Data);
ALWAYS_INLINE void USART_ResetBitsRTOR(USART_TypeDef *USARTx, uint32_t Data);

ALWAYS_INLINE void USART_SetRQR(USART_TypeDef *USARTx, uint32_t Data);

ALWAYS_INLINE uint32_t USART_GetISR(USART_TypeDef *USARTx);

ALWAYS_INLINE void USART_SetICR(USART_TypeDef *USARTx, uint32_t Data);
ALWAYS_INLINE uint32_t USART_GetICR(USART_TypeDef *USARTx);
ALWAYS_INLINE void USART_SetBitsICR(USART_TypeDef *USARTx, uint32_t Data);
ALWAYS_INLINE void USART_ResetBitsICR(USART_TypeDef *USARTx, uint32_t Data);

ALWAYS_INLINE uint32_t USART_GetRDR(USART_TypeDef *USARTx);

ALWAYS_INLINE void USART_SetTDR(USART_TypeDef *USARTx, uint32_t Data);



  //  USARTx->CR1 Functions 
ALWAYS_INLINE void USART_SetCR1(USART_TypeDef *USARTx, uint32_t Data)
{
  USARTx->CR1 = Data;
}
ALWAYS_INLINE uint32_t USART_GetCR1(USART_TypeDef *USARTx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x0]" : "=r" (ret) : "r" (USARTx));
  return ret;
}
ALWAYS_INLINE void USART_SetBitsCR1(USART_TypeDef *USARTx, uint32_t Data)
{
  USARTx->CR1 |= Data;
}
ALWAYS_INLINE void USART_ResetBitsCR1(USART_TypeDef *USARTx, uint32_t Data)
{
  USARTx->CR1 &= Data;
}



  //  USARTx->CR2 Functions 
ALWAYS_INLINE void USART_SetCR2(USART_TypeDef *USARTx, uint32_t Data)
{
  USARTx->CR2 = Data;
}
ALWAYS_INLINE uint32_t USART_GetCR2(USART_TypeDef *USARTx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x4]" : "=r" (ret) : "r" (USARTx));
  return ret;
}
ALWAYS_INLINE void USART_SetBitsCR2(USART_TypeDef *USARTx, uint32_t Data)
{
  USARTx->CR2 |= Data;
}
ALWAYS_INLINE void USART_ResetBitsCR2(USART_TypeDef *USARTx, uint32_t Data)
{
  USARTx->CR2 &= Data;
}



  //  USARTx->CR3 Functions 
ALWAYS_INLINE void USART_SetCR3(USART_TypeDef *USARTx, uint32_t Data)
{
  USARTx->CR3 = Data;
}
ALWAYS_INLINE uint32_t USART_GetCR3(USART_TypeDef *USARTx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x8]" : "=r" (ret) : "r" (USARTx));
  return ret;
}
ALWAYS_INLINE void USART_SetBitsCR3(USART_TypeDef *USARTx, uint32_t Data)
{
  USARTx->CR3 |= Data;
}
ALWAYS_INLINE void USART_ResetBitsCR3(USART_TypeDef *USARTx, uint32_t Data)
{
  USARTx->CR3 &= Data;
}



  //  USARTx->BRR Functions 
ALWAYS_INLINE void USART_SetBRR(USART_TypeDef *USARTx, uint32_t Data)
{
  USARTx->BRR = Data;
}
ALWAYS_INLINE uint32_t USART_GetBRR(USART_TypeDef *USARTx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0xc]" : "=r" (ret) : "r" (USARTx));
  return ret;
}
ALWAYS_INLINE void USART_SetBitsBRR(USART_TypeDef *USARTx, uint32_t Data)
{
  USARTx->BRR |= Data;
}
ALWAYS_INLINE void USART_ResetBitsBRR(USART_TypeDef *USARTx, uint32_t Data)
{
  USARTx->BRR &= Data;
}



  //  USARTx->GTPR Functions 
ALWAYS_INLINE void USART_SetGTPR(USART_TypeDef *USARTx, uint32_t Data)
{
  USARTx->GTPR = Data;
}
ALWAYS_INLINE uint32_t USART_GetGTPR(USART_TypeDef *USARTx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x10]" : "=r" (ret) : "r" (USARTx));
  return ret;
}
ALWAYS_INLINE void USART_SetBitsGTPR(USART_TypeDef *USARTx, uint32_t Data)
{
  USARTx->GTPR |= Data;
}
ALWAYS_INLINE void USART_ResetBitsGTPR(USART_TypeDef *USARTx, uint32_t Data)
{
  USARTx->GTPR &= Data;
}



  //  USARTx->RTOR Functions 
ALWAYS_INLINE void USART_SetRTOR(USART_TypeDef *USARTx, uint32_t Data)
{
  USARTx->RTOR = Data;
}
ALWAYS_INLINE uint32_t USART_GetRTOR(USART_TypeDef *USARTx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x14]" : "=r" (ret) : "r" (USARTx));
  return ret;
}
ALWAYS_INLINE void USART_SetBitsRTOR(USART_TypeDef *USARTx, uint32_t Data)
{
  USARTx->RTOR |= Data;
}
ALWAYS_INLINE void USART_ResetBitsRTOR(USART_TypeDef *USARTx, uint32_t Data)
{
  USARTx->RTOR &= Data;
}



  //  USARTx->RQR Functions 
ALWAYS_INLINE void USART_SetRQR(USART_TypeDef *USARTx, uint32_t Data)
{
  USARTx->RQR = Data;
}



  //  USARTx->ISR Functions 
ALWAYS_INLINE uint32_t USART_GetISR(USART_TypeDef *USARTx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x1c]" : "=r" (ret) : "r" (USARTx));
  return ret;
}


  //  USARTx->ICR Functions 
ALWAYS_INLINE void USART_SetICR(USART_TypeDef *USARTx, uint32_t Data)
{
  USARTx->ICR = Data;
}
ALWAYS_INLINE uint32_t USART_GetICR(USART_TypeDef *USARTx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x20]" : "=r" (ret) : "r" (USARTx));
  return ret;
}
ALWAYS_INLINE void USART_SetBitsICR(USART_TypeDef *USARTx, uint32_t Data)
{
  USARTx->ICR |= Data;
}
ALWAYS_INLINE void USART_ResetBitsICR(USART_TypeDef *USARTx, uint32_t Data)
{
  USARTx->ICR &= Data;
}



  //  USARTx->RDR Functions 
ALWAYS_INLINE uint32_t USART_GetRDR(USART_TypeDef *USARTx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x24]" : "=r" (ret) : "r" (USARTx));
  return ret;
}

  //  USARTx->TDR Functions 
ALWAYS_INLINE void USART_SetTDR(USART_TypeDef *USARTx, uint32_t Data)
{
  USARTx->TDR = Data;
}







#endif
