

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

//  .type  PERIPH_WaitTillReset, %function
  //.global PERIPH_WaitTillReset
PERIPH_WaitTillReset:
  ldr r2, [r0]
  ldr r12, =0xE000ED04
  and r2, r1
  cmp r1, r2
bne EXIT //if reset then exit. otherwise call the scheduler
  mov r3, #1 << 26
  str r3, [r12]
b PERIPH_WaitTillReset

 // .type  PERIPH_WaitTillSet, %function
 // .global PERIPH_WaitTillSet
PERIPH_WaitTillSet:
  ldr r2, [r0]
  ldr r12, =0xE000ED04
  and r2, r1
  cmp r1, r2
beq EXIT //if set then exit
  mov r3, #1 << 26
  str r3, [r12]
b PERIPH_WaitTillSet

//  .type  PERIPH_GetStatus, %function
//  .global PERIPH_GetStatus
PERIPH_GetStatus:
  ldr r0, [r0]
  ands r0, r1
bx lr

