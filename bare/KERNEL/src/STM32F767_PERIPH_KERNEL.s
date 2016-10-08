

.syntax unified
.cpu cortex-m7
.fpu fpv5-d16
.thumb

    .section .text.PERIPH

//ICSR Reg For calling systick
// 0xE000ED04
// orr 1 << 26 //call systick bit

EXIT:
bx lr

  .type  PERIPH_WaitTillFlagReset, %function
  .global PERIPH_WaitTillFlagReset
PERIPH_WaitTillFlagReset:
  ldr r2, [r0]
  ands r2, r1
  ldr r2, =0xE000ED04
beq EXIT //if reset then exit
  ldr r3, [r2]
  orr r3, #1 << 26
  str r3, [r2]
b PERIPH_WaitTillFlagReset

  .type  PERIPH_WaitTillFlagSet, %function
  .global PERIPH_WaitTillFlagSet
PERIPH_WaitTillFlagSet:
  ldr r2, [r0]
  ands r2, r1
  ldr r2, =0xE000ED04
bne EXIT //if set then exit
  ldr r3, [r2]
  orr r3, #1 << 26
  str r3, [r2]
b PERIPH_WaitTillFlagSet

  .type  PERIPH_CheckFlag, %function
  .global PERIPH_CheckFlag
PERIPH_CheckFlag:
  ldr r0, [r0]
  ands r0, r1
bx lr

