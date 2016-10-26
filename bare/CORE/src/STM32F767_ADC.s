//
//
//
//
//

.syntax unified
.cpu cortex-m7
.fpu fpv5-d16
.thumb

    .section .text.ADC


  .type ADC_Configure, %function
  .global ADC_Configure
ADC_Configure:
  str r1, [r0, #4] //store CR1
  ldr r1, [sp, #8] //load ADC_SMPLOW arg
  str r2, [r0, #8] //str CR2
  str r1, [r0,#0x10] //store ADC_SMPLOW to ADC_SMPR2
  ldr r2, [sp] //load ADC LTR arg
  ldr r1, [sp, #0x4] //load ADC_SMPHIGH arg
  str r3, [r0, #0x24] //store ADC_HTR
  str r1, [r0, #0xc]  //store ADC_SMPHIGH to ADC_SMPR1
  str r2, [r0, #0x28] //store ADC_LTR
bx lr













