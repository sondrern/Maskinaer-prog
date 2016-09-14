.syntax unified

.include "efm32gg.s"

/////////////////////////////////////////////////////////////////////////////
//
// Exception vector table
// This table contains addresses for all exception handlers
//
/////////////////////////////////////////////////////////////////////////////

.section .vectors

	.long   stack_top               /* Top of Stack                 */
	.long   _reset                  /* Reset Handler                */
	.long   dummy_handler           /* NMI Handler                  */
	.long   dummy_handler           /* Hard Fault Handler           */
	.long   dummy_handler           /* MPU Fault Handler            */
	.long   dummy_handler           /* Bus Fault Handler            */
	.long   dummy_handler           /* Usage Fault Handler          */
	.long   dummy_handler           /* Reserved                     */
	.long   dummy_handler           /* Reserved                     */
	.long   dummy_handler           /* Reserved                     */
	.long   dummy_handler           /* Reserved                     */
	.long   dummy_handler           /* SVCall Handler               */
	.long   dummy_handler           /* Debug Monitor Handler        */
	.long   dummy_handler           /* Reserved                     */
	.long   dummy_handler           /* PendSV Handler               */
	.long   dummy_handler           /* SysTick Handler              */

	/* External Interrupts */
	.long   dummy_handler
	.long   gpio_handler            /* GPIO even handler */
	.long   dummy_handler
	.long   dummy_handler
	.long   dummy_handler
	.long   dummy_handler
	.long   dummy_handler
	.long   dummy_handler
	.long   dummy_handler
	.long   dummy_handler
	.long   dummy_handler
	.long   gpio_handler            /* GPIO odd handler */
	.long   dummy_handler
	.long   dummy_handler
	.long   dummy_handler
	.long   dummy_handler
	.long   dummy_handler
	.long   dummy_handler
	.long   dummy_handler
	.long   dummy_handler
	.long   dummy_handler
	.long   dummy_handler
	.long   dummy_handler
	.long   dummy_handler
	.long   dummy_handler
	.long   dummy_handler
	.long   dummy_handler
	.long   dummy_handler
	.long   dummy_handler
	.long   dummy_handler
	.long   dummy_handler
	.long   dummy_handler
	.long   dummy_handler
	.long   dummy_handler
	.long   dummy_handler
	.long   dummy_handler
	.long   dummy_handler
	.long   dummy_handler
	.long   dummy_handler

.section .text

/////////////////////////////////////////////////////////////////////////////
//
// Reset handler
// The CPU will start executing here after a reset
//
/////////////////////////////////////////////////////////////////////////////

	.globl  _reset
	.type   _reset, %function
	.thumb_func
_reset: 

	BL init_clk
	BL init_leds
	BL init_buttons
	BL init_interupt
	//BL poll
	BL init_sleep
	WFI

	 


////////////////////////////////////////////////////////////////////////////
          
	.thumb_func
init_clk:
	ldr r1, =CMU_BASE
 	ldr r2, [r1, #CMU_HFPERCLKEN0]
 	mov r3, #1 
 	lsl r3, r3, #CMU_HFPERCLKEN0_GPIO
 	orr r2, r2, r3
 	str r2, [r1, #CMU_HFPERCLKEN0]
 	BX LR
	
////////////////////////////////////////////////////////////////////////////
          
	.thumb_func
init_leds:
	ldr r1, =GPIO_PA_BASE
	mov r2, #0x2
	str r2, [r1, #GPIO_CTRL]
	ldr r2, =0x55555555
	str r2, [r1, #GPIO_MODEH]
	BX LR

////////////////////////////////////////////////////////////////////////////
          
	.thumb_func
init_buttons:
	ldr r1, =GPIO_PC_BASE 
	ldr r2, =0x33333333
	str r2, [r1, #GPIO_MODEL]
	mov r2, #0xff
	str r2, [r1, #GPIO_DOUT]
	BX LR

////////////////////////////////////////////////////////////////////////////
          
	.thumb_func
poll:	
	ldr r1, =GPIO_PC_BASE
	ldr r2, =GPIO_PA_BASE
	while: 	
		ldr r3, [r1, #GPIO_DIN]
		lsl r3, r3, #8
		str r3, [r2, #GPIO_DOUT]
		b while
	
	

/////////////////////////////////////////////////////////////////////////////
//
// Interupt init
//
/////////////////////////////////////////////////////////////////////////////

    .thumb_func
init_interupt:  
	ldr r1, =GPIO_BASE
	ldr r2, =0x22222222
	str r2, [r1, #GPIO_EXTIPSELL]
	
	mov r2, #0xff
	str r2, [r1, #GPIO_EXTIFALL]
	
	mov r2, #0xff
	str r2, [r1, #GPIO_EXTIRISE]
	
	mov r2, #0xff
	str r2, [r1, #GPIO_IEN]
	
	ldr r1, =ISER0
	ldr r2, =0x802
	
	str r2, [r1]
	
	BX LR
	
	
////////////////////////////////////////////////////////////////////////////
          
	.thumb_func
init_sleep:
	ldr r1, =SCR
 	mov r2, #6
 	str r2, [r1]
 	BX LR	

	
/////////////////////////////////////////////////////////////////////////////
//
// GPIO handler
// The CPU will jump here when there is a GPIO interrupt
//
/////////////////////////////////////////////////////////////////////////////

    .thumb_func
gpio_handler: 
	ldr r1, =GPIO_BASE
	ldr r2, [r1, #GPIO_IF]
	str r2, [r1, #GPIO_IFC]
		
    
    ldr r1, =GPIO_PC_BASE
	ldr r2, =GPIO_PA_BASE

	ldr r3, [r1, #GPIO_DIN]
	lsl r3, r3, #8
	str r3, [r2, #GPIO_DOUT]
	
	BX LR
	
	
	 

/////////////////////////////////////////////////////////////////////////////

    .thumb_func
dummy_handler:  
	b .  // do nothing

