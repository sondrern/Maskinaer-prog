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
	//b .  // do nothing
	
ldr r1, =CMU_BASE

	 //load current value of HFPERCLK ENBALE
	 ldr r2, [r1, #CMU_HFPERCLKEN0]

	 //Set bit for GPIO clk
	 mov r3, #1 
	 lsl r3, r3, #CMU_HFPERCLKEN0_GPIO
	 orr r2, r2, r3

	 //Store new value 
	 str r2, [r1, #CMU_HFPERCLKEN0]
	 
	 ldr r1, =GPIO_PA_BASE
		
	//set high drive strength
	mov r2, #0x2
	str r2, [r1, #GPIO_CTRL]
	
	//set pins 8-15 output
	ldr r2, =0x55555555
	str r2, [r1, #GPIO_MODEH]
		
	ldr r1, =GPIO_PC_BASE 
 	
	//Set pins 0-7 to input
	ldr r2, =0x33333333
	str r2, [r1, #GPIO_MODEL]
	
	//Enable interal pull-up
	mov r2, #0xff
	str r2, [r1, #GPIO_DOUT]
	
	ldr r1, =GPIO_PC_BASE
	ldr r2, =GPIO_PA_BASE
while: 	
	ldr r3, [r1, #GPIO_DIN]
	lsl r3, r3, #8
	str r3, [r2, #GPIO_DOUT]
	b while
	
	

/////////////////////////////////////////////////////////////////////////////
//
// GPIO handler
// The CPU will jump here when there is a GPIO interrupt
//
/////////////////////////////////////////////////////////////////////////////

    .thumb_func
gpio_handler:  
	b .  // do nothing

/////////////////////////////////////////////////////////////////////////////

    .thumb_func
dummy_handler:  
	b .  // do nothing

