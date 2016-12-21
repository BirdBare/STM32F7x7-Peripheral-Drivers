//
//
//
//
//




#include "STM32F767_HTU21D.h"


void HTU21D_EnableGeneral(uint32_t ClockFreqHz)
{
  SysTick_EnableTimer();
  RCC_EnableClock((struct RCCo *)&GPIOBo);
  GPIO_SetPins(&GPIOBo, GPIO_PIN_6 | GPIO_PIN_7,GPIO_MODE_ALTERNATE,
    GPIO_OUTTYPE_OPENDRAIN,GPIO_OUTSPEED_VHIGH,
    GPIO_PUPD_PU,GPIO_ALTFUNCTION_4);
  I2C_EnableClock(I2C_CLOCK_I2C1);
  I2C_EnableMaster(HTU21D_I2Cx, I2C_CR1_PE | I2C_CR1_ANFOFF,ClockFreqHz,0);
  DelayMilli(15);
}

void HTU21D_Reset(void)
{
  if(I2C_Start(HTU21D_I2Cx, I2C_CR2_AUTOEND | I2C_CR2_WRITE | I2C_CR2_START,
    HTU21D_ADDRESS,1))
  {
    PERIPH_WaitTillSet(&HTU21D_I2Cx->ISR, I2C_ISR_TXE);
    I2C_Send(HTU21D_I2Cx,HTU21D_RST);
    DelayMilli(15);
  }
}

void HTU21D_SetUserReg(uint8_t HTU21D_MESRES, uint8_t HTU21D_HEATER)
{
  if(I2C_Start(HTU21D_I2Cx, I2C_CR2_AUTOEND | I2C_CR2_WRITE | I2C_CR2_START,
    HTU21D_ADDRESS,2))
  {
    PERIPH_WaitTillSet(&HTU21D_I2Cx->ISR, I2C_ISR_TXE);
    I2C_Send(HTU21D_I2Cx,HTU21D_WRUSER);
    PERIPH_WaitTillSet(&HTU21D_I2Cx->ISR, I2C_ISR_TXE);
    I2C_Send(HTU21D_I2Cx,HTU21D_MESRES | HTU21D_HEATER);
  }
}

uint16_t HTU21D_GetData(uint8_t HTU21D_TEMPHUM)
{
  uint16_t data = 0;

  if(I2C_Start(HTU21D_I2Cx, I2C_CR2_AUTOEND | I2C_CR2_WRITE | I2C_CR2_START,
    HTU21D_ADDRESS,1))
  {
    PERIPH_WaitTillSet(&HTU21D_I2Cx->ISR, I2C_ISR_TXE);
    I2C_Send(HTU21D_I2Cx,HTU21D_TEMPHUM);
    
  if(I2C_Start(HTU21D_I2Cx, I2C_CR2_AUTOEND | I2C_CR2_READ | I2C_CR2_START,
    HTU21D_ADDRESS,2))
    {
      PERIPH_WaitTillSet(&HTU21D_I2Cx->ISR, I2C_ISR_RXNE);
      data = I2C_Receive(HTU21D_I2Cx);
      data <<= 8;
      PERIPH_WaitTillSet(&HTU21D_I2Cx->ISR, I2C_ISR_RXNE);
      data |= (uint16_t)I2C_Receive(HTU21D_I2Cx);
    }
  }
  return data;
}

float HTU21D_GetTemp(void)
{
  return (((175.72 * (float)HTU21D_GetData(HTU21D_TEMP)) / 65536.0) - 46.85);
}

float HTU21D_GetHumidity(void)
{
  return (((125.0 * (float)(HTU21D_GetData(HTU21D_HUM) & (~0b10))) / 65536.0) - 6.0);
}

