//
//
//
//
//



#ifndef STM32F767_I2C_H
#define STM32F767_I2C_H

#include "BARE_STM32F767.h"

//  PROTOTYPES FOR SIMPLE REGISTER FUNCTIONS
//  ALL FORCED INLINE SO THEY DO NOT USE FLASH SPACE
ALWAYS_INLINE void I2C_SetCR1(I2C_TypeDef *I2Cx, uint32_t Data);
ALWAYS_INLINE uint32_t I2C_GetCR1(I2C_TypeDef *I2Cx);
ALWAYS_INLINE void I2C_SetBitsCR1(I2C_TypeDef *I2Cx, uint32_t Data);
ALWAYS_INLINE void I2C_ResetBitsCR1(I2C_TypeDef *I2Cx, uint32_t Data);

ALWAYS_INLINE void I2C_SetCR2(I2C_TypeDef *I2Cx, uint32_t Data);
ALWAYS_INLINE uint32_t I2C_GetCR2(I2C_TypeDef *I2Cx);
ALWAYS_INLINE void I2C_SetBitsCR2(I2C_TypeDef *I2Cx, uint32_t Data);
ALWAYS_INLINE void I2C_ResetBitsCR2(I2C_TypeDef *I2Cx, uint32_t Data);

ALWAYS_INLINE void I2C_SetOAR1(I2C_TypeDef *I2Cx, uint32_t Data);
ALWAYS_INLINE uint32_t I2C_GetOAR1(I2C_TypeDef *I2Cx);
ALWAYS_INLINE void I2C_SetBitsOAR1(I2C_TypeDef *I2Cx, uint32_t Data);
ALWAYS_INLINE void I2C_ResetBitsOAR1(I2C_TypeDef *I2Cx, uint32_t Data);

ALWAYS_INLINE void I2C_SetOAR2(I2C_TypeDef *I2Cx, uint32_t Data);
ALWAYS_INLINE uint32_t I2C_GetOAR2(I2C_TypeDef *I2Cx);
ALWAYS_INLINE void I2C_SetBitsOAR2(I2C_TypeDef *I2Cx, uint32_t Data);
ALWAYS_INLINE void I2C_ResetBitsOAR2(I2C_TypeDef *I2Cx, uint32_t Data);

ALWAYS_INLINE void I2C_SetTIMINGR(I2C_TypeDef *I2Cx, uint32_t Data);
ALWAYS_INLINE uint32_t I2C_GetTIMINGR(I2C_TypeDef *I2Cx);
ALWAYS_INLINE void I2C_SetBitsTIMINGR(I2C_TypeDef *I2Cx, uint32_t Data);
ALWAYS_INLINE void I2C_ResetBitsTIMINGR(I2C_TypeDef *I2Cx, uint32_t Data);

ALWAYS_INLINE void I2C_SetTIMEOUTR(I2C_TypeDef *I2Cx, uint32_t Data);
ALWAYS_INLINE uint32_t I2C_GetTIMEOUTR(I2C_TypeDef *I2Cx);
ALWAYS_INLINE void I2C_SetBitsTIMEOUTR(I2C_TypeDef *I2Cx, uint32_t Data);
ALWAYS_INLINE void I2C_ResetBitsTIMEOUTR(I2C_TypeDef *I2Cx, uint32_t Data);

ALWAYS_INLINE uint32_t I2C_GetISR(I2C_TypeDef *I2Cx);

ALWAYS_INLINE void I2C_SetICR(I2C_TypeDef *I2Cx, uint32_t Data);

ALWAYS_INLINE uint32_t I2C_GetPECR(I2C_TypeDef *I2Cx);

ALWAYS_INLINE void I2C_SetTXDR(I2C_TypeDef *I2Cx, uint32_t Data);

ALWAYS_INLINE uint32_t I2C_GetRXDR(I2C_TypeDef *I2Cx);




#define I2C_CLOCK_I2C1 RCC_APB1ENR_I2C1EN
#define I2C_CLOCK_I2C2 RCC_APB1ENR_I2C2EN
#define I2C_CLOCK_I2C3 RCC_APB1ENR_I2C3EN
#define I2C_CLOCK_I2C4 RCC_APB1ENR_I2C4EN

#define I2C_EnableClock(I2C_CLOCK) \
  RCC->APB1ENR |= (I2C_CLOCK)
  
#define I2C_DisableClock(I2C_CLOCK) \
  RCC->APB1RSTR |= (I2C_CLOCK)  


#define I2C_Disable(I2Cx) \
  (I2Cx)->CR1 &= (uint16_t)(~(I2C_CR1_PE))


#define I2C_CR1_SMB_PEC  I2C_CR1_PECEN
#define I2C_CR1_SMB_ALERT  I2C_CR1_ALERTEN
#define I2C_CR1_SMB_DEFAULT  I2C_CR1_SMBDEN
#define I2C_CR1_SMB_HOST  I2C_CR1_SMBHEN
#define I2C_CR1_GENERAL  I2C_CR1_GCEN
//#define I2C_CR1_NOSTRETCH  I2C_CR1_NOSTRETCH
//#define I2C_CR1_SCB  I2C_CR1_SBC
//#define I2C_CR1_RXDMAEN  I2C_CR1_RXDMAEN
//#define I2C_CR1_TXDMAEN  I2C_CR1_TXDMAEN
//#define I2C_CR1_ANFOFF  I2C_CR1_ANFOFF
#define I2C_CR1_DNF_1CLK  
#define I2C_CR1_DNF_2CLK  
#define I2C_CR1_DNF_3CLK 
#define I2C_CR1_DNF_4CLK
#define I2C_CR1_DNF_5CLK  
#define I2C_CR1_DNF_6CLK  
#define I2C_CR1_DNF_7CLK  
#define I2C_CR1_DNF_8CLK  
#define I2C_CR1_DNF_9CLK  
#define I2C_CR1_DNF_10CLK 
#define I2C_CR1_DNF_11CLK  
#define I2C_CR1_DNF_12CLK  
#define I2C_CR1_DNF_13CLK  
#define I2C_CR1_DNF_14CLK  
#define I2C_CR1_DNF_15CLK  
//#define I2C_CR1_ERRIE  I2C_CR1_ERRIE
//#define I2C_CR1_TCIE  I2C_CR1_TCIE
//#define I2C_CR1_STOPIE  I2C_CR1_STOPIE
//#define I2C_CR1_NACKIE  I2C_CR1_NACKIE
//#define I2C_CR1_ADDRIE  I2C_CR1_ADDRIE
//#define I2C_CR1_RXIE  I2C_CR1_RXIE
//#define I2C_CR1_TXIE  I2C_CR1_TXIE
//#define I2C_CR1_PE  I2C_CR1_PE

extern void I2C_EnableMaster(I2C_TypeDef *I2Cx,uint32_t I2C_CR1,uint32_t Timing,
  uint32_t Timeout_reg);



/*__attribute__((optimize("O0")))
static void I2C_EnableMaster(I2C_TypeDef *I2Cx,
  uint32_t I2C_CUBEMX_TIMINGR_DATA)
{
  I2C_Disable(I2Cx);
  
  I2Cx->OAR1 = 0;  
  I2Cx->OAR2 = 0;  

  uint32_t timing = 48000000 / I2C_CUBEMX_TIMINGR_DATA;

  int32_t prescale = 1;
  while(timing/prescale > 510)
  {
    prescale++;
  }
  timing /= prescale;

  timing -= 25;
  if(I2C_CUBEMX_TIMINGR_DATA > 93950)
    timing -=25;
  
  timing /= 2;

  I2Cx->TIMINGR = (timing | timing << 8 | (prescale-1) << 28); 

  I2Cx->CR1 |= I2C_CR1_PE |(15 << 8) ;
}*/


//#define I2C_CR2_PECBYTE  I2C_CR2_PECBYTE
//#define I2C_CR2_AUTOEND  I2C_CR2_AUTOEND
//#define I2C_CR2_RELOAD  I2C_CR2_RELOAD
//#define I2C_CR2_NACK  I2C_CR2_NACK
//#define I2C_CR2_STOP  I2C_CR2_STOP
//#define I2C_CR2_START  I2C_CR2_START
#define I2C_CR2_HEADER  I2C_CR2_HEAD10R
//#define I2C_CR2_ADD10  I2C_CR2_ADD10
#define I2C_CR2_WRITE  0
#define I2C_CR2_READ  I2C_CR2_RD_WRN

extern uint32_t I2C_Start(I2C_TypeDef *I2Cx, uint32_t I2C_CR2, uint32_t SlaveAdd,
  uint32_t NumData);


/*#define I2C_AUTOEND_ON I2C_CR2_AUTOEND
#define I2C_AUTOEND_OFF 0 
#define I2C_RW_READ 0x1
#define I2C_RW_WRITE 0x0
static uint8_t I2C_Start(I2C_TypeDef *I2Cx, uint32_t I2C_SLAVE_ADDRESS_RW,
  uint32_t I2C_AUTOEND, uint8_t I2C_NUM_DATA_TO_RDWR)
{
  I2Cx->CR2 = I2C_SLAVE_ADDRESS_RW;

  I2Cx->CR2 |= I2C_AUTOEND;
  
  I2Cx->CR2 |= (I2C_SLAVE_ADDRESS_RW << 10) & I2C_CR2_RD_WRN; 

  I2Cx->CR2 |= (I2C_NUM_DATA_TO_RDWR << 16);

  I2Cx->CR2 |= I2C_CR2_START;

  uint32_t NACKSTATUS = 0;
  while((I2Cx->CR2 & I2C_CR2_START) != 0)
  {
    asm("");
  }  
  
  NACKSTATUS = I2Cx->ISR & I2C_ISR_NACKF;  

  if(NACKSTATUS != 0)
  {
    I2Cx->ICR &= !(I2C_ICR_NACKCF);
    return 0;
  }
  return 1;
}*/

extern void I2C_Send(I2C_TypeDef *I2Cx, uint32_t I2C_DATA);
/* WHILE REMOVED IN ASM{
  while((I2Cx->ISR & I2C_ISR_TXE) == 0)
    asm("");
  I2Cx->TXDR = I2C_DATA;
}*/

extern uint32_t I2C_Receive(I2C_TypeDef *I2Cx);
/* WHILE REMOVED IN ASM{
  while((I2Cx->ISR & I2C_ISR_RXNE) == 0)
    asm("");
  return (uint8_t)(I2Cx->RXDR);
}*/


























//  I2Cx->CR1 functions
ALWAYS_INLINE void I2C_SetCR1(I2C_TypeDef *I2Cx, uint32_t Data)
{
  I2Cx->CR1 = Data;
}
ALWAYS_INLINE uint32_t I2C_GetCR1(I2C_TypeDef *I2Cx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1]" :"=r" (ret) : "r" (I2Cx));
  return ret;
}
ALWAYS_INLINE void I2C_SetBitsCR1(I2C_TypeDef *I2Cx, uint32_t Data)
{
  I2Cx->CR1 |= Data;
}
ALWAYS_INLINE void I2C_ResetBitsCR1(I2C_TypeDef *I2Cx, uint32_t Data)
{
  I2Cx->CR1 &= Data;
}





//  I2Cx->CR2 functions
ALWAYS_INLINE void I2C_SetCR2(I2C_TypeDef *I2Cx, uint32_t Data)
{
  I2Cx->CR2 = Data;
}
ALWAYS_INLINE uint32_t I2C_GetCR2(I2C_TypeDef *I2Cx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #4]" :"=r" (ret) : "r" (I2Cx));
  return ret;
}
ALWAYS_INLINE void I2C_SetBitsCR2(I2C_TypeDef *I2Cx, uint32_t Data)
{
  I2Cx->CR2 |= Data;
}
ALWAYS_INLINE void I2C_ResetBitsCR2(I2C_TypeDef *I2Cx, uint32_t Data)
{
  I2Cx->CR2 &= Data;
}





//  I2Cx->OAR1 functions
ALWAYS_INLINE void I2C_SetOAR1(I2C_TypeDef *I2Cx, uint32_t Data)
{
  I2Cx->OAR1 = Data;
}
ALWAYS_INLINE uint32_t I2C_GetOAR1(I2C_TypeDef *I2Cx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #8]" :"=r" (ret) : "r" (I2Cx));
  return ret;
}
ALWAYS_INLINE void I2C_SetBitsOAR1(I2C_TypeDef *I2Cx, uint32_t Data)
{
  I2Cx->OAR1 |= Data;
}
ALWAYS_INLINE void I2C_ResetBitsOAR1(I2C_TypeDef *I2Cx, uint32_t Data)
{
  I2Cx->OAR1 &= Data;
}





//  I2Cx->OAR2 functions
ALWAYS_INLINE void I2C_SetOAR2(I2C_TypeDef *I2Cx, uint32_t Data)
{
  I2Cx->OAR2 = Data;
}
ALWAYS_INLINE uint32_t I2C_GetOAR2(I2C_TypeDef *I2Cx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0xc]" :"=r" (ret) : "r" (I2Cx));
  return ret;
}
ALWAYS_INLINE void I2C_SetBitsOAR2(I2C_TypeDef *I2Cx, uint32_t Data)
{
  I2Cx->OAR2 |= Data;
}
ALWAYS_INLINE void I2C_ResetBitsOAR2(I2C_TypeDef *I2Cx, uint32_t Data)
{
  I2Cx->OAR2 &= Data;
}





//  I2Cx->TIMINGR functions
ALWAYS_INLINE void I2C_SetTIMINGR(I2C_TypeDef *I2Cx, uint32_t Data)
{
  I2Cx->TIMINGR = Data;
}
ALWAYS_INLINE uint32_t I2C_GetTIMINGR(I2C_TypeDef *I2Cx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x10]" :"=r" (ret) : "r" (I2Cx));
  return ret;
}
ALWAYS_INLINE void I2C_SetBitsTIMINGR(I2C_TypeDef *I2Cx, uint32_t Data)
{
  I2Cx->TIMINGR |= Data;
}
ALWAYS_INLINE void I2C_ResetBitsTIMINGR(I2C_TypeDef *I2Cx, uint32_t Data)
{
  I2Cx->TIMINGR &= Data;
}





//  I2Cx->TIMEOUTR functions
ALWAYS_INLINE void I2C_SetTIMEOUTR(I2C_TypeDef *I2Cx, uint32_t Data)
{
  I2Cx->TIMEOUTR = Data;
}
ALWAYS_INLINE uint32_t I2C_GetTIMEOUTR(I2C_TypeDef *I2Cx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, 0x14]" :"=r" (ret) : "r" (I2Cx));
  return ret;
}
ALWAYS_INLINE void I2C_SetBitsTIMEOUTR(I2C_TypeDef *I2Cx, uint32_t Data)
{
  I2Cx->TIMEOUTR |= Data;
}
ALWAYS_INLINE void I2C_ResetBitsTIMEOUTR(I2C_TypeDef *I2Cx, uint32_t Data)
{
  I2Cx->TIMEOUTR &= Data;
}





//  I2Cx->ISR functions
ALWAYS_INLINE void I2C_SetISR(I2C_TypeDef *I2Cx, uint32_t Data)
{
  I2Cx->ISR = Data;
}
ALWAYS_INLINE uint32_t I2C_GetISR(I2C_TypeDef *I2Cx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x18]" :"=r" (ret) : "r" (I2Cx));
  return ret;
}



//  I2Cx->ICR functions
ALWAYS_INLINE void I2C_SetICR(I2C_TypeDef *I2Cx, uint32_t Data)
{
  I2Cx->ICR = Data;
}




//  I2Cx->PECR functions
ALWAYS_INLINE uint32_t I2C_GetPECR(I2C_TypeDef *I2Cx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x20]" :"=r" (ret) : "r" (I2Cx));
  return ret;
}





//  I2Cx->TXDR AND I2Cx->RXDR functions
ALWAYS_INLINE void I2C_SetTXDR(I2C_TypeDef *I2Cx, uint32_t Data)
{
  I2Cx->TXDR = Data;
}
ALWAYS_INLINE uint32_t I2C_GetRXDR(I2C_TypeDef *I2Cx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x24]" :"=r" (ret) : "r" (I2Cx));
  return ret;
}



























#endif
