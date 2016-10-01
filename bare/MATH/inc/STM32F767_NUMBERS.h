//
//
//
//
//



#ifndef STM32F407_NUMBERS_H
#define STM32F407_NUMBERS_H

static uint32_t NUMBERS_Map(uint32_t x, uint32_t oldrange,
   uint32_t newrange)
{
  return (float)(x * newrange) / (float)oldrange;
}
static uint32_t NUMBERS_Constrain(uint32_t amt,uint32_t lo, uint32_t high)
{
  return ((amt)<=lo)?lo:((amt)>(high)?(high):(amt));
}








#endif
