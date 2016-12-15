#ifndef __SYSTEM_STM32F7XX_H
#define __SYSTEM_STM32F7XX_H

#ifdef __cplusplus
 extern "C" {
#endif 

#define SystemCoreClock _FCPU         
extern uint32_t _FCPU;  //CPU Freq 
extern uint32_t _FAHB;  //CPU Freq 
extern uint32_t _FAPB1;  //CPU Freq 
extern uint32_t _FAPB2;  //CPU Freq 

void SystemInit(void);
void SetSysClock(void);

#ifdef __cplusplus
}
#endif

#endif /*__SYSTEM_STM32F7XX_H */

