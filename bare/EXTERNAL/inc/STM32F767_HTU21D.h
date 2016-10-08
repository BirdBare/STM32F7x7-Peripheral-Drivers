//
//
//
//
//

#ifndef STM32F407_HTU21D_H
#define STM32F407_HTU21D_H



#include "stm32f767xx.h"
#include "STM32F767_GPIO.h"
#include "STM32F767_I2C.h"
#include "STM32F767_SYSTICK.h"
#include "STM32F767_PERIPH.h"

#define HTU21D_TEMP 0xE3
#define HTU21D_HUM 0xE5
#define HTU21D_WRUSER 0xE6
#define HTU21D_RDUSER 0xE7
#define HTU21D_RST 0xFE

#define HTU21D_I2Cx I2C1
#define HTU21D_ADDRESS 0x80

extern void HTU21D_EnableGeneral(uint32_t ClockFreqHz);
/*{
  SysTick_EnableTimer();
  GPIO_EnableClock(GPIO_CLOCK_GPIOB);
  GPIO_SetPins(GPIOB, GPIO_PIN_6 | GPIO_PIN_7,GPIO_MODE_ALTERNATE,
    GPIO_OUTTYPE_OPENDRAIN,GPIO_OUTSPEED_VHIGH,
    GPIO_PUPD_PU,GPIO_ALTFUNCTION_4);
  I2C_EnableClock(I2C_CLOCK_I2C1);
  I2C_EnableMaster(HTU21D_I2Cx, I2C_CR1_PE | I2C_CR1_ANFOFF,ClockFreqHz,0);
  DelayMilli(15);
}*/

extern void HTU21D_Reset(void);
/*{
  if(I2C_Start(HTU21D_I2Cx, I2C_CR2_AUTOEND | I2C_CR2_WRITE | I2C_CR2_START,
    HTU21D_ADDRESS,1))
  {
    PERIPH_LoopTillFlagSet(&HTU21D_I2Cx->ISR, I2C_ISR_TXE);
    I2C_Send(HTU21D_I2Cx,HTU21D_RST);
    DelayMilli(15);
  }
}*/

#define HTU21D_MESRES_RH12T14 0b00000000
#define HTU21D_MESRES_RH8T12 0b00000001
#define HTU21D_MESRES_RH10T13 0b10000000
#define HTU21D_MESRES_RH11T11 0b10000001

#define HTU21D_HEATER_ON 0b100
#define HTU21D_HEATER_OFF 0b000

extern void HTU21D_SetUserReg(uint8_t HTU21D_MESRES, uint8_t HTU21D_HEATER);
/*{
  if(I2C_Start(HTU21D_I2Cx, I2C_CR2_AUTOEND | I2C_CR2_WRITE | I2C_CR2_START,
    HTU21D_ADDRESS,2))
  {
    PERIPH_LoopTillFlagSet(&HTU21D_I2Cx->ISR, I2C_ISR_TXE);
    I2C_Send(HTU21D_I2Cx,HTU21D_WRUSER);
    PERIPH_LoopTillFlagSet(&HTU21D_I2Cx->ISR, I2C_ISR_TXE);
    I2C_Send(HTU21D_I2Cx,HTU21D_MESRES | HTU21D_HEATER);
  }
}

static uint16_t HTU21D_GetData(uint8_t HTU21D_TEMPHUM)
{
  uint16_t data = 0;

  if(I2C_Start(HTU21D_I2Cx, I2C_CR2_AUTOEND | I2C_CR2_WRITE | I2C_CR2_START,
    HTU21D_ADDRESS,1))
  {
    PERIPH_LoopTillFlagSet(&HTU21D_I2Cx->ISR, I2C_ISR_TXE);
    I2C_Send(HTU21D_I2Cx,HTU21D_TEMPHUM);
    
  if(I2C_Start(HTU21D_I2Cx, I2C_CR2_AUTOEND | I2C_CR2_READ | I2C_CR2_START,
    HTU21D_ADDRESS,2))
    {
      PERIPH_LoopTillFlagSet(&HTU21D_I2Cx->ISR, I2C_ISR_RXNE);
      data = I2C_Receive(HTU21D_I2Cx);
      data <<= 8;
      PERIPH_LoopTillFlagSet(&HTU21D_I2Cx->ISR, I2C_ISR_RXNE);
      data |= (uint16_t)I2C_Receive(HTU21D_I2Cx);
    }
  }
  return data;
}*/

extern float HTU21D_GetTemp(void);
/*{
  return (((175.72 * (float)HTU21D_GetData(HTU21D_TEMP)) / 65536.0) - 46.85);
}*/

extern float HTU21D_GetHumidity(void);
/*{
  return (((125.0 * (float)(HTU21D_GetData(HTU21D_HUM) & (~0b10))) / 65536.0) - 6.0);
}
*/
#endif
