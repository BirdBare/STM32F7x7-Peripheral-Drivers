

.syntax unified
.cpu cortex-m7
.fpu fpv5-d16
.thumb

    .section .text.PERIPH

  .type  PERIPH_WaitTillReset, %function
  .global PERIPH_WaitTillReset
PERIPH_WaitTillReset:
  ldr r2, [r0]
  and r2, r1
  cmp r2, r1
beq PERIPH_WaitTillReset
bx lr

  .type  PERIPH_WaitTillSet, %function
  .global PERIPH_WaitTillSet
PERIPH_WaitTillSet:
  ldr r2, [r0]
  and r2, r1
  cmp r2, r1
bne PERIPH_WaitTillSet
bx lr

  .type  PERIPH_GetStatus, %function
  .global PERIPH_GetStatus
PERIPH_GetStatus:
  ldr r0, [r0]
  ands r0, r1
bx lr

