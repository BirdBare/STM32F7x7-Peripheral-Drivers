

.syntax unified
.cpu cortex-m7
.fpu fpv5-d16
.thumb

      .section ._ITCM.SCHEDULING

  .type  DelayMilli, %function
  .global DelayMilli
DelayMilli:
ldr r1, =SysTick_MilliSec //load SysTick_MilliSec address
ldr r2, [r1]  //load ref

Loop:
  ldr r3, [r1] //load current MilliSec
  sub r3, r2 //sub ref from millisec to get waited millisec
  cmp r0, r3 //sub (ref-millisec) from desired millisec 
bhi Loop //loop is desired millisec is still higher than waiting millisec

bx lr




  .type  SysTick_Handler, %function
  .global SysTick_Handler
SysTick_Handler:
  
  ldr r3, =SysTick_MilliSec //gets address of SysTick_MilliSec variable 
  
  ldr r2, [r3]  //load value

  add r2, #1 //add 1

  str r2, [r3]  //store value

bx lr








