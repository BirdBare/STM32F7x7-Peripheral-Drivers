//
//
//
//
//



#ifndef STM32F767_GPIO_H
#define STM32F767_GPIO_H

#include "stm32f7xx.h"

//*****  RESET AND CLOCK CONTROL  **********

/*
   Reset and Clock control functions to enable and disable GPIO clocks
*/
#define GPIO_CLOCK_GPIOA RCC_AHB1ENR_GPIOAEN
#define GPIO_CLOCK_GPIOB RCC_AHB1ENR_GPIOBEN
#define GPIO_CLOCK_GPIOC RCC_AHB1ENR_GPIOCEN
#define GPIO_CLOCK_GPIOD RCC_AHB1ENR_GPIODEN
#define GPIO_CLOCK_GPIOE RCC_AHB1ENR_GPIOEEN
#define GPIO_CLOCK_GPIOF RCC_AHB1ENR_GPIOFEN
#define GPIO_CLOCK_GPIOG RCC_AHB1ENR_GPIOGEN
#define GPIO_CLOCK_GPIOH RCC_AHB1ENR_GPIOHEN
#define GPIO_CLOCK_GPIOI RCC_AHB1ENR_GPIOIEN

#define GPIO_EnableClock(GPIO_CLOCK) \
  RCC->AHB1ENR |= (GPIO_CLOCK)

#define GPIO_DisableClock(GPIO_CLOCK) \
  RCC->AHB1RSTR |= (GPIO_CLOCK)

//****** GPIO ********

#define GPIO_PIN_0         ((uint16_t)0x0001)  /* Pin 0 selected */
#define GPIO_PIN_1         ((uint16_t)0x0002)  /* Pin 1 selected */
#define GPIO_PIN_2         ((uint16_t)0x0004)  /* Pin 2 selected */
#define GPIO_PIN_3         ((uint16_t)0x0008)  /* Pin 3 selected */
#define GPIO_PIN_4         ((uint16_t)0x0010)  /* Pin 4 selected */
#define GPIO_PIN_5         ((uint16_t)0x0020)  /* Pin 5 selected */
#define GPIO_PIN_6         ((uint16_t)0x0040)  /* Pin 6 selected */
#define GPIO_PIN_7         ((uint16_t)0x0080)  /* Pin 7 selected */
#define GPIO_PIN_8         ((uint16_t)0x0100)  /* Pin 8 selected */
#define GPIO_PIN_9         ((uint16_t)0x0200)  /* Pin 9 selected */
#define GPIO_PIN_10        ((uint16_t)0x0400)  /* Pin 10 selected */
#define GPIO_PIN_11        ((uint16_t)0x0800)  /* Pin 11 selected */
#define GPIO_PIN_12        ((uint16_t)0x1000)  /* Pin 12 selected */
#define GPIO_PIN_13        ((uint16_t)0x2000)  /* Pin 13 selected */
#define GPIO_PIN_14        ((uint16_t)0x4000)  /* Pin 14 selected */
#define GPIO_PIN_15        ((uint16_t)0x8000)  /* Pin 15 selected */
#define GPIO_PIN_ALL       ((uint16_t)0xFFFF)  /* All pins selected */

#define GPIO_NO_USE ((uint32_t)0x00)

#define GPIO_MODE_INPUT ((uint32_t)0b00)
#define GPIO_MODE_OUTPUT ((uint32_t)0b01)
#define GPIO_MODE_ALTERNATE ((uint32_t)0b10)
#define GPIO_MODE_ANALOG ((uint32_t)0b11) 

#define GPIO_OUTTYPE_PUSHPULL ((uint32_t)0b0)
#define GPIO_OUTTYPE_OPENDRAIN ((uint32_t)0b1)

#define GPIO_OUTSPEED_LOW ((uint32_t)0b00)
#define GPIO_OUTSPEED_MED ((uint32_t)0b01)
#define GPIO_OUTSPEED_HIGH ((uint32_t)0b10)
#define GPIO_OUTSPEED_VHIGH ((uint32_t)0b11)

#define GPIO_PUPD_OFF ((uint32_t)0b00)
#define GPIO_PUPD_PU ((uint32_t)0b01)
#define GPIO_PUPD_PD ((uint32_t)0b10)

#define GPIO_ALTFUNCTION_OFF ((uint32_t)0x00)
#define GPIO_ALTFUNCTION_0 ((uint32_t)0x00)
#define GPIO_ALTFUNCTION_1 ((uint32_t)0x01)
#define GPIO_ALTFUNCTION_2 ((uint32_t)0x02)
#define GPIO_ALTFUNCTION_3 ((uint32_t)0x03)
#define GPIO_ALTFUNCTION_4 ((uint32_t)0x04)
#define GPIO_ALTFUNCTION_5 ((uint32_t)0x05)
#define GPIO_ALTFUNCTION_6 ((uint32_t)0x06)
#define GPIO_ALTFUNCTION_7 ((uint32_t)0x07)
#define GPIO_ALTFUNCTION_8 ((uint32_t)0x08)
#define GPIO_ALTFUNCTION_9 ((uint32_t)0x09)
#define GPIO_ALTFUNCTION_10 ((uint32_t)0x0A)
#define GPIO_ALTFUNCTION_11 ((uint32_t)0x0B)
#define GPIO_ALTFUNCTION_12 ((uint32_t)0x0C)
#define GPIO_ALTFUNCTION_13 ((uint32_t)0x0D)
#define GPIO_ALTFUNCTION_14 ((uint32_t)0x0E)
#define GPIO_ALTFUNCTION_15 ((uint32_t)0x0F)

/* 
    GPIO functions to change the mode of the pin
*/
extern void GPIO_SetPins(GPIO_TypeDef *GPIO_PORT,
  const uint32_t GPIO_PIN,const uint32_t GPIO_MODE, 
  const uint32_t GPIO_OUTTYPE, const uint32_t GPIO_OUTSPEED, 
  const uint32_t GPIO_PUPD,const uint32_t GPIO_ALTFUNCTION);
/*{
  for(uint8_t count = 0; count < 16; count++)
  {
    if(GPIO_PIN & ((uint32_t)0b1 << count)) //!= 0)
    {
      uint32_t count2 = count << 1;
      uint32_t count2reset = (uint32_t)0b11 << count2;

      //Sets Pin Mode
      GPIO_PORT->MODER &= ~((uint32_t)(count2reset)); 
      //Sets Pin mode to reset state 
    
      GPIO_PORT->MODER |= (GPIO_MODE << (count2)); 
      //Bitshift left by 1 to multiply by two
      //
      
      //Sets Pin Output Type
      GPIO_PORT->OTYPER &= ~((uint32_t)0b1 << count); 
      //Sets Pin type to reset state
      
      GPIO_PORT->OTYPER |= (GPIO_OUTTYPE << count);
      //Does not need to multiply by 2. Check register.
      //
      
      //Sets Pin Speed
      GPIO_PORT->OSPEEDR &= ~((uint32_t)(count2reset)); 
      //Sets Pin speed to reset state
      
      GPIO_PORT->OSPEEDR |= (GPIO_OUTSPEED << (count2)); 
      //Bitshift left by 1 to multiply by two
      //

      //Sets Pin Pullup or Pulldown
      GPIO_PORT->PUPDR &= ~((uint32_t)(count2reset)); 
      //Sets Pin resistor to reset state
      
      GPIO_PORT->PUPDR |= (GPIO_PUPD << (count2)); 
      //Bitshift left by 1 to multiply by two
      //  
      
      count2 = (count & 0b111) << 2;

      GPIO_PORT->AFR[count >> 3] &= ~((uint32_t)0b1111 << 
        ((count2))); 
      //Sets Pin Alternate Function to reset GPIO
      
         GPIO_PORT->AFR[count >> 3] |= (GPIO_ALTFUNCTION << 
           ((count2)));
      //Sets Pin Alternate Function
    }
  }
}
*/
extern void GPIO_SetOutput(GPIO_TypeDef *GPIO_PORT,uint32_t GPIO_PIN);

extern void GPIO_ResetOutput(GPIO_TypeDef *GPIO_PORT,uint32_t GPIO_PIN);

extern void GPIO_ChangeOutput(GPIO_TypeDef *GPIOx,uint32_t setGPIO_PIN,uint32_t resetGPIO_PIN);

extern void GPIO_ToggleOutput(GPIO_TypeDef *GPIO_PORT,uint32_t GPIO_PIN);

extern uint32_t GPIO_GetInState(GPIO_TypeDef *GPIO_PORT,uint32_t GPIO_PIN);

extern uint32_t GPIO_GetOutState(GPIO_TypeDef *GPIO_PORT,uint32_t GPIO_PIN); 

#endif
