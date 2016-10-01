//
//
//
  int32_t x;
  int32_t y;



#ifndef STM32F407_MATH_H
#define STM32F407_MATH_H

struct MATH_POINT
{
  uint32_t x;
  uint32_t y;
};

static int32_t MATH_abs(int32_t val)
{
  if(val < 0)
  {
    return val * -1;
  } 
  return val;
}

static uint32_t MATH_EXP(uint32_t number, uint16_t exp)
{
  uint32_t result = 1;  

  while (exp){
    if (exp&1){
      result *= number;
    }
    exp >>=1 ;
    number *= number;
  }
  return result;
}







#endif
