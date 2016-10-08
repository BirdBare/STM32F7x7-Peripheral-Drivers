

.syntax unified
.cpu cortex-m7
.fpu fpv5-d16
.thumb

    .section .text.PERIPH

  .type  PERIPH_WaitTillFlagReset, %function
  .global PERIPH_WaitTillFlagReset
PERIPH_WaitTillFlagReset:
  ldr r2, [r0]
  ands r2, r1
bne PERIPH_WaitTillFlagReset
bx lr

  .type  PERIPH_WaitTillFlagSet, %function
  .global PERIPH_WaitTillFlagSet
PERIPH_WaitTillFlagSet:
  ldr r2, [r0]
  ands r2, r1
beq PERIPH_WaitTillFlagSet
bx lr

  .type  PERIPH_CheckFlag, %function
  .global PERIPH_CheckFlag
PERIPH_CheckFlag:
  ldr r0, [r0]
  ands r0, r1
bx lr

