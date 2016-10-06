

.syntax unified
.cpu cortex-m7
.fpu fpv5-d16
.thumb

  .section .text.I2C

  .type  I2C_EnableMaster, %function
  .global I2C_EnableMaster
I2C_EnableMaster:

  push {r4-r5}

  str r3, [r0, #20] //store timeout
  ldr r3, =#48000000 //load clock frequency

  mov r12, #0
  str r12, [r0, #8]
  str r12, [r0, #12]
  //reset OAR1 and OAR2 

  udiv r3, r3, r2 //get number of cycles from timing
  mov r12, #1 //setup prescaler

  NOTLESS:
    udiv r4, r3, r12
    add r12, #1
    cmp r4, #510
  bhi NOTLESS

  sub r4, #25
  lsr r4, #1 

  sub r12, #2
  orr r4, r4, r4, lsl #8
  orr r4, r4, r12, lsl #28

  str r4, [r0, #16] //store timing

  str r1, [r0] //store CR1

  pop {r4-r5}
bx lr

  .type  I2C_Start, %function
  .global I2C_Start
I2C_Start:

  orr r1, r2
  orr r1, r1, r3, lsl #16
  //Peice together CR2 reg

  str r1, [r0, #4]
  //store CR2

  STARTLOOP:
    ldr r1, [r0, #4]
    ands r1, #1 << 13
  bne STARTLOOP
  //loop until start bit is set

  ldr r1, [r0, #24] //load status reg
  mov r2, #1 << 4 
  ands r1, r2 //see if NACK flag is set
  
  beq NACKPASS
    str r2, [r0, #28]
    mov r0, #0
  NACKPASS:

bx lr

  .type  I2C_Send, %function
  .global I2C_Send
I2C_Send:
  str r1, [r0, #40]
bx lr

  .type  I2C_Receive, %function
  .global I2C_Receive
I2C_Receive:
  ldr r0, [r0, #36]
bx lr










