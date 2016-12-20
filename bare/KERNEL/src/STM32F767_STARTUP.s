//
//
//
//
//




  .syntax unified
  .cpu cortex-m7
  .fpu softvfp
  .thumb

.global  g_pfnVectors
.global  Default_Handler

/**
 * @brief  This is the code that gets called when the processor first
 *          starts execution following a reset event. Only the absolutely
 *          necessary set is performed, after which the application
 *          supplied main() routine is called. 
 * @param  None
 * @retval : None
*/

CopyDataInit:
  ldr  r3, [r2], #4
  str  r3, [r0], #4
    
LoopCopyDataInit:
  cmp  r0, r1
  bcc  CopyDataInit
  mov pc, lr
 

    .section  .text.Reset_Handler
  .weak  Reset_Handler
  .type  Reset_Handler, %function
Reset_Handler:  

	//FILL bss zero

	ldr  r0, =_sbss
  ldr  r1, = _ebss
  movs  r2, #0

  b  LoopFillZerobss

	FillZerobss:
		str  r2, [r0], #4
    
	LoopFillZerobss:
		cmp  r0, r1
		bcc  FillZerobss


/* Copy the data segment initializers from flash to SRAM */  
  
  ldr r0, =_sdata
  ldr r1, =_edata
  ldr r2, =_sidata
  bl  LoopCopyDataInit
  
	ldr r0, =_sITCM
  ldr r1, =_eITCM
  ldr r2, =_siITCM
  bl  LoopCopyDataInit

	ldr r0, =_sSRAM
  ldr r1, =_eSRAM
  ldr r2, =_siSRAM
  bl  LoopCopyDataInit

	//FINISHED COPYING DATA INTO RAM

  /* Call the clock system initialization function.*/
  bl  SystemInit   

/* Set Stack pointer for non interrupt processes */
  mov   r0, #0b10         /* set Stack Pointer to Process stack pointer */
  msr CONTROL, r0 
  ldr   sp, =_ePstack     /* set Process stack pointer */

/* Call the application's entry point.*/
  bl  main
  bx  lr    
.size  Reset_Handler, .-Reset_Handler

/******************************************************************************
*
* The minimal vector table for a Cortex M7. Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
* 
*******************************************************************************/
   .section  .isr_vector,"a",%progbits
  .type  g_pfnVectors, %object
  .size  g_pfnVectors, .-g_pfnVectors
   
   
g_pfnVectors:
  .word  _estack
  .word  Reset_Handler


