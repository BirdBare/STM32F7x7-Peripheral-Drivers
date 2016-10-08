

.syntax unified
.cpu cortex-m7
.fpu fpv5-d16
.thumb

      .section ._ITCM.SCHEDULING


  .type  SysTick_Handler, %function
  .global SysTick_Handler
SysTick_Handler:
  
  ldr r3, =SysTick_MilliSec //gets address of SysTick_MilliSec variable 
  
  ldr r2, [r3]

  add r2, #1

  str r2, [r3]

bx lr








