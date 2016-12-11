//
//
//
//
//



#ifndef STM32F767_STREAM_H
#define STM32F767_STREAM_H

#include "stm32f7xx.h"
#include "STM32F767_BUFFER.h"

#define STREAM_HASHSIZE 100

/* this is for communication between peripherals like SPI and I2C, UART, and
 * other high transfer speed peripherals.
 */

extern int8_t rowoff[STREAM_HASHSIZE];



struct PIPE
{
  void *pipe0;  //points to an address 
  void *pipe1;  //points to another address 
                  //Owner pipe 0 is input
                  //      pipe 1 is output
                  //
                  //User pipe 0 is output
                  //     pipe 1 is input

  uint32_t (*Read)(void *memorylocation, void *data); 
    //can handle any data size through typecasting

  uint32_t (*Write)(void *memorylocation, uint32_t data);

  uint16_t num_connected; 
  uint16_t flags;
};
  #define PIPE_DEAD
  #define PIPE_




#endif
