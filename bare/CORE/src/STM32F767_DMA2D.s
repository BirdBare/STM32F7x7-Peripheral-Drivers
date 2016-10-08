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

  push {r0-r4,lr}
  //save caller save registers because we need to wait for DMA2D to Finish

  ldr r0, =0x4002B000 //Load DMA2D CR Reg address
  mov r1, #1
  //Set Registers for function
  bl PERIPH_WaitTillFlagReset //check if flag is reset and act accordingly
                              //depending on NO_KERNEL vs KERNEL
  //OLD LOOP TO WAIT FOR DMA2D TRANSACTION TO FINISH
  //Reg2MemWaitStart:
    //ldr r0, [r4]
    //ands r0, #0x1
  //bne Reg2MemWaitStart //wait for start bit to be zero

  pop {r1-r4}

  ldr lr, [sp, #8]
  str r1, [r0, #0x3c]
  str r2, [r0, #0x34]
  str r3, [r0, #0x38]
  str r4, [r0, #0x44]
  str lr, [r0, #0x40]
  //store values in registers for next DMA2D transfer


  
  ldr r2, [r0]
  ldr r1, =0b110000000000000001
  orr r2, r1
  //preserve old register values incase interrupts are set
  //DONT NEED TO AND THE VALUE BECAUSE ALL NEEDED VALUES WILL BE SET 
  //        START AND MODE

  str r2, [r0]
  //Start DMA2D Transfer by storing value

pop {r4, pc} 
//finished. Return to caller function



  .type DMA2D_Mem2Mem, %function
  .global DMA2D_Mem2Mem
DMA2D_Mem2Mem:

  push {r0-r4,lr}
  //save caller save registers because we need to wait for DMA2D to Finish

  ldr r0, =0x4002B000 //Load DMA2D CR Reg address
  mov r1, #1
  //Set Registers for function
  bl PERIPH_WaitTillFlagReset
  //wait for DMA2D to finish previous transaction

  pop {r1-r4}
  
  ldr lr, [sp, #8] //load 5th parameter from stack FGOR
  str r1, [r0, #0xc]
  str r2, [r0, #0x3c]
  ldr r1, [sp, #12] //load 6th parameter from stack OOR
  str r3, [r0, #0x1c]
  str r4, [r0, #0x44]
  str lr, [r0, #0x10]
  str r1, [r0, #0x40]
  //set DMA2D registers


  ldr r3, [r0]
  ldr r1, =~0b110000000000000001
  mov r2, #1
  and r3, r1
  orr r3, r2
  //preserve old register values incase interrupts are set
   
  str r3, [r0]
  //Start DMA2D Transfer by storing value

pop {r4, pc}








