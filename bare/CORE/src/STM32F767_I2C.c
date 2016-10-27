//
//
//
//
//



#include "STM32F767_I2C.h"


uint32_t I2C_CalculateTimingReg(uint32_t FreqHz)
{
  uint32_t timing = 48000000 / FreqHz;

  uint32_t prescale = 1;
  do
  {
    prescale++;
  }
  while(timing/prescale > 510);

  timing /= prescale;

  timing -= 25;
  
  timing >>= 1;

  return( timing | timing << 8 | (prescale-2) << 28); 
}





