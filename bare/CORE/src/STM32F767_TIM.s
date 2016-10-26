//
//
//
//
//

.syntax unified
.cpu cortex-m7
.fpu fpv5-d16
.thumb

    .section .text.TIM


  .type _TIM_EnableTimer, %function
  .global _TIM_EnableTimer
_TIM_EnableTimer:
  str r2, [r0, #0xc]

  str r3, [r0, #0x28]

  str r1, [r0] //store CR1 and CR2 into respective registers

bx lr











