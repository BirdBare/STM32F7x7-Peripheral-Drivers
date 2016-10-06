

.syntax unified
.cpu cortex-m7
.fpu fpv5-d16
.thumb

    .section .text.GPIO

//  .type  GPIO_, %function
//  .global GPIO_
//GPIO_:

  .type  GPIO_SetOutput, %function
  .global GPIO_SetOutput
GPIO_SetOutput:
  str r1, [r0, #24]
bx lr
  .type  GPIO_ResetOutput, %function
  .global GPIO_ResetOutput
GPIO_ResetOutput:
  lsl r1, #16
  str r1, [r0, #24]
bx lr
  .type  GPIO_ChangeOutput, %function
  .global GPIO_ChangeOutput
GPIO_ChangeOutput:
  lsl r2, #16
  orr r1, r2
  str r1, [r0, #24]
bx lr
  .type  GPIO_ToggleOutput, %function
  .global GPIO_ToggleOutput
GPIO_ToggleOutput:
  ldr r2, [r0, #20]
  eor r1, r2
  str r1, [r0, #20]
bx lr
  .type  GPIO_GetInState, %function
  .global GPIO_GetInState
GPIO_GetInState:
  ldr r0, [r0, #16]
  ands r0, r1
bx lr
  .type  GPIO_GetOutState, %function
  .global GPIO_GetOutState
GPIO_GetOutState:
  ldr r0, [r0, #20]
  ands r0, r1
bx lr

  .type  GPIO_SetPins, %function
  .global GPIO_SetPins
GPIO_SetPins:

  push {r4-r12, lr}
  add sp, #40
  //push all callee save registers to stack and add that value to sp
  // to get to location of function variables

  mov lr, #16
  //set number of times to do the loop

  ldmia sp, {r10-r12}
  //r0 GPIO
  //r1 GPIO_PINS
  //r2 VAR 1
  //r3 VAR 2
  //r10 VAR 3
  //r11 VAR 4
  //r12 VAR 5

  sub sp, #40

  mov r4, #1 << 15
  //pin test and 0b1 reset bit
  mov r5, #0b11 << 30
  //0b11 reset bits
  //starts at highest bits because counter starts at highest bits

    SETPINSFORLOOP:

      subs lr, #1
      //counter. goes for 16 counts

      and r6, r4, r1
      cbz r6, SETPINSSKIPPIN 
      //check if pin spot is set. if not we dont do anything to it.

      lsl r6, lr, #1 
      //get bit spot for new 0b11 register value

      // LOAD MODE Register
      ldr r7, [r0]
      //load mode register value
      lsl r8, r2, r6
      //push mode setting to correct register spot
      bic r7, r5
      orr r7, r8
      //Reset pins values then orr set them to mode value
      str r7, [r0]  
      //store the new value in the mode register

      //LOAD SPEED register
      ldr r7, [r0, #8]
      lsl r8, r10, r6
      bic r7, r5
      orr r7, r8
      str r7, [r0, #8]

      //LOAD PUPD register
      ldr r7, [r0, #12]
      lsl r8, r11, r6
      bic r7, r5
      orr r7, r8
      str r7, [r0, #12]

      //LOAD TYPE Register
      ldr r7, [r0, #4]
      lsl r8, r11, lr
      bic r7, r4
      orr r7, r8
      str r7, [r0, #4]

      //LOAD ALT Register
      
      and r6, lr, #0b111
      lsl r6, #2
      //get bit spot for alt function pin

      lsr r9, lr, #3
      lsl r9, #2
      add r9, #32
      //get location of Alt func register (low and high regs)

      //load alt func register. reset pin.
      ldr r7, [r0, r9]
      //load alt function register value
      mov r8, #0b1111
      //set reset mask
      lsl r8, r6
      //shift reset mask to correct spot
      bic r7, r8
      //reset
      lsl r8, r12, r6
      //shift alt function value to correct spot
      orr r7, r8
      //set
      str r7, [r0, r9]
      //store


    SETPINSSKIPPIN:
      lsr r4, #1
      lsr r5, #2
      //move to next pin
    bne SETPINSFORLOOP

pop {r4-r12, pc}
//done


