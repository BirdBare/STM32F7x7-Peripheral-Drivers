//
//
//
//
//



/* !!!!!!!!!!!!ATTENTION!!!!!!!!!!!!!!!!


    SPI.o MUST BE ADDED TO LIST OF OBJECTS IN MAKEFILE TO USE THIS LIBRARU


    MUST

*/




#ifndef STM32F767_SPI_H
#define STM32F767_SPI_H

#include "stm32f7xx.h"

#define SPI_CLOCK_SPI1 RCC_APB2ENR_SPI1EN 
#define SPI_CLOCK_SPI4 RCC_APB2ENR_SPI4EN 
#define SPI_CLOCK_SPI5 RCC_APB2ENR_SPI5EN 
#define SPI_CLOCK_SPI6 RCC_APB2ENR_SPI6EN 
/* APB2 */

#define SPI_CLOCK_SPI2 RCC_APB1ENR_SPI2EN  
#define SPI_CLOCK_SPI3 RCC_APB1ENR_SPI3EN
/* APB1 */

#define SPI_EnableClockAPB2(SPI_CLOCK) \
    RCC->APB2ENR |= (SPI_CLOCK)

#define SPI_EnableClockAPB1(SPI_CLOCK) \
    RCC->APB1ENR |= (SPI_CLOCK)
  
#define SPI_DisableClockAPB2(SPI_CLOCK) \
    RCC->APB2RSTR |= (SPI_CLOCK)
    
#define SPI_DisableClockAPB1(SPI_CLOCK) \
    RCC->APB1RSTR |= (SPI_CLOCK)


/* SPI CR1 OPTIONS 

  REQUIRED OPTIONS:
      
    SPI_CR1_CLKDIV - CLOCK IS DIVIDED FROM PERIPHERAL CLOCK

*/
#define SPI_CR1_HALFDUPLEX SPI_CR1_BIDIMODE
#define SPI_CR1_HALFDUPLEX_RECEIVE 0
#define SPI_CR1_HALFDUPLEX_TRANSFER SPI_CR1_BIDIOE
//Half Duplex Communication

#define SPI_CR1_CRC SPI_CR1_CRCEN
#define SPI_CR1_CRC_8bit 0
#define SPI_CR1_CRC_16bit SPI_CR1_CRCL
//CRC packet error checking enable and setting set

//#define SPI_CR1_LSBFIRST SPI_CR2_LSBFIRST
//Transfer LSB first instead of MSB

//#define SPI_CR1_MSTR SPI_CR1_MSTR
//#define SPI_CR1_SPE SPI_CR1_SPE
// SPI enable

#define SPI_CR1_CLKDIV_2     0
#define SPI_CR1_CLKDIV_4     SPI_CR1_BR_0
#define SPI_CR1_CLKDIV_8     SPI_CR1_BR_1
#define SPI_CR1_CLKDIV_16    (SPI_CR1_BR_1 | SPI_CR1_BR_0)
#define SPI_CR1_CLKDIV_32    SPI_CR1_BR_2
#define SPI_CR1_CLKDIV_64    (SPI_CR1_BR_2 | SPI_CR1_BR_0)
#define SPI_CR1_CLKDIV_128   (SPI_CR1_BR_2 | SPI_CR1_BR_1)
#define SPI_CR1_CLKDIV_256   (SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0)
//Baud rate selection from peripheral clock

#define SPI_CR1_MODE_0 (uint16_t) 0b00
#define SPI_CR1_MODE_1 (uint16_t) 0b01
#define SPI_CR1_MODE_2 (uint16_t) 0b10
#define SPI_CR1_MODE_3 (uint16_t) 0b11
//SPI Mode Selection

/* SPI CR2 OPTIONS 

  REQUIRED OPTIONS:

    SPI_CR2_DSIZE - if SPI_CR2_DSIZE !> 8 then add SPI_CR2_FIFO_8bit

*/
#define SPI_CR2_LDMA_TXODD SPI_CR2_LDMA_TX
#define SPI_CR2_LDMA_RXODD SPI_CR2_LDMA_RX
//Number dma data to transfer for data packing

#define SPI_CR2_FIFO_8bit SPI_CR2_FRXTH
//RX fifo size 8 bit or 16bit default

#define SPI_CR2_DSIZE_4 ((uint16_t)0b0011 << 8)
#define SPI_CR2_DSIZE_5 ((uint16_t)0b0100 << 8)
#define SPI_CR2_DSIZE_6 ((uint16_t)0b0101 << 8)
#define SPI_CR2_DSIZE_7 ((uint16_t)0b0110 << 8)
#define SPI_CR2_DSIZE_8 ((uint16_t)0b0111 << 8)
#define SPI_CR2_DSIZE_9 ((uint16_t)0b1000 << 8)
#define SPI_CR2_DSIZE_10 ((uint16_t)0b1001 << 8)
#define SPI_CR2_DSIZE_11 ((uint16_t)0b1010 << 8)
#define SPI_CR2_DSIZE_12 ((uint16_t)0b1011 << 8)
#define SPI_CR2_DSIZE_14 ((uint16_t)0b1100 << 8)
#define SPI_CR2_DSIZE_15 ((uint16_t)0b1110 << 8)
#define SPI_CR2_DSIZE_16 ((uint16_t)0b1111 << 8)
//Data size for SPI

//#define SPI_CR2_TXEIE SPI_CR2_TXEIE //TX empty
//#define SPI_CR2_RXNEIE SPI_CR2_RXNEIE //RX not empty
//#define SPI_CR2_ERRIE SPI_CR2_ERRIE //Error
//Interrupt Enables

#define SPI_CR2_FORMAT_TI
//Data frame format TI or Moto default

#define SPI_CR2_PULSESS SPI_CR2_NSSP
//Pulse SS each data or Pulse SS when SPI on/off/on transition default

//#define SPI_CR2_TXDMAEN SPI_CR2_TXDMAEN
//#define SPI_CR2_RXDMAEN SPI_CR2_RXDMAEN
//Enable DMA REQUESTS


extern void SPI_EnableMaster(SPI_TypeDef *SPIx, uint32_t SPI_CR1, 
  uint32_t SPI_CR2, uint32_t SPI_CRC_Polynomial);

extern void SPI_Disable(SPI_TypeDef *SPIx);

extern void SPI_Send8(SPI_TypeDef *SPIx, uint32_t SPI_DATA);

extern uint32_t SPI_Receive8(SPI_TypeDef *SPIx);

extern void SPI_Send16(SPI_TypeDef *SPIx, uint32_t SPI_DATA);

extern uint32_t SPI_Receive16(SPI_TypeDef *SPIx);

//extern void PERIPH_LoopTillFlagSet(volatile void *FlagRegAddress, uint32_t flag);

//extern void PERIPH_LoopTillFlagReset(volatile void *FlagRegAddress, uint32_t flag);

//extern uint32_t PERIPH_CheckFlag(volatile void *FlagRegAddress, uint32_t flag);

#define SPI_WaitTransfer(SPIx) \
  PERIPH_WaitTillReset(&(SPIx->SR), SPI_SR_BSY)
/*
static void SPI_WaitTransfer(SPI_TypeDef *SPIx)
{ 
  while((SPIx->SR & SPI_SR_BSY) != 0) 
    asm(""); 
}*/



#endif
