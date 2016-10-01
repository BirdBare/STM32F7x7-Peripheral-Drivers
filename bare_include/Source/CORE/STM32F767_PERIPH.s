

.syntax unified
.cpu cortex-m7
.fpu softvfp
.thumb

    .section .text.PERIPH

  .type  PERIPH_LoopTillFlagReset, %function
  .global PERIPH_LoopTillFlagReset
PERIPH_LoopTillFlagReset:
  ldr r2, [r0]
  ands r2, r1
bne PERIPH_LoopTillFlagReset
bx lr

  .type  PERIPH_LoopTillFlagSet, %function
  .global PERIPH_LoopTillFlagSet
PERIPH_LoopTillFlagSet:
  ldr r2, [r0]
  ands r2, r1
beq PERIPH_LoopTillFlagSet
bx lr

  .type  PERIPH_CheckFlag, %function
  .global PERIPH_CheckFlag
PERIPH_CheckFlag:
  ldr r0, [r0]
  ands r0, r1
bx lr

