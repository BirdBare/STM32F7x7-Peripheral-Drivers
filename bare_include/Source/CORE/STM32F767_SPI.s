

.syntax unified
.cpu cortex-m7
.fpu softvfp
.thumb

    .section .text.SPI
  .type  SPI_EnableMaster, %function
  .global SPI_EnableMaster
SPI_EnableMaster:
  str r3, [r0, #16] //store CRC Polynomial into Polynomial Reg

  orr r2, #0b100 //Add SSOE bit to CR2

  mov r3, #0 //prepare to reset I2S Registers

  str r2, [r0, #4] //Store CR2 Values into CR2 REG

  str r3, [r0, #28] // Reset I2S Config Reg

  str r1, [r0] //Set CR1 and to enable SPI
bx lr

  .type  SPI_Disable, %function
  .global SPI_Disable
SPI_Disable:
  mov r1, #0
  str r1, [r0]
bx lr

  .type  SPI_Send8, %function
  .global SPI_Send8
SPI_Send8:
  strb r1, [r0, #12]
bx lr

  .type  SPI_Receive8, %function
  .global SPI_Receive8
SPI_Receive8:
  ldrb r0, [r0,#12]
bx lr

.type  SPI_Send16, %function
  .global SPI_Send16
SPI_Send16:
  strh r1, [r0, #12]
bx lr

  .type  SPI_Receive16, %function
  .global SPI_Receive16
SPI_Receive16:
  ldrh r0, [r0,#12]
bx lr

