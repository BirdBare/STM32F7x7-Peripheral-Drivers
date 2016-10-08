//
//
//
//
//

.syntax unified
.cpu cortex-m7
.fpu fpv5-d16
.thumb

    .section .text.DMA2D


  .type DMA2D_Reg2Mem, %function
  .global DMA2D_Reg2Mem
DMA2D_Reg2Mem:

  push {r4,lr}
  ldr r4, =0x4002B000 //Load DMA2D CR Reg address
  ldr lr, [sp, #8]
  str r0, [r4, #0x3c]
  str r1, [r4, #0x34]
  str r2, [r4, #0x38]
  str r3, [r4, #0x44]
  str lr, [r4, #0x40]
  //store values in registers for next DMA2D transfer


  mov r0, r4
  mov r1, #1
  //Set Registers for function
  bl PERIPH_WaitTillFlagReset //check if flag is reset and act accordingly
                              //depending on NO_KERNEL vs KERNEL
  //Reg2MemWaitStart:
    //ldr r0, [r4]
    //ands r0, #0x1
  //bne Reg2MemWaitStart //wait for start bit to be zero


  ldr r0, =0b110000000000000001
  str r0, [r4]
  //Start DMA2D Transfer

pop {r4, pc} 
//finished. Return to caller function













