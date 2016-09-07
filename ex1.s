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
	
ldr r1, cmu_base_addr
	ldr r2, [r1, #CMU_HFPERCLKEN0]
	mov r3, #1
	lsl r3, r3, #CMU_HFPERCLKEN0_GPIO
	orr r2, r2, r3
	str r2, [r1, #CMU_HFPERCLKEN0]
	
	cmu_base_addr:
	.long CMU_BASE



	ldr r1, gpio_pa_base_addr	
	ldr r2, [r1, #GPIO_CTRL]
	mov r3, #0x2
	orr r2, r2, r3
	str r2, [r1, #GPIO_CTRL]
	
	gpio_pa_base_addr:
	.long GPIO_PA_BASE




	
	ldr r2, [r1, #GPIO_MODEH]
	mov r3, #0x55555555
	orr r2, r2, r3
	str r2, [r1, #GPIO_MODEH]



	
	ldr r2, [r1, #GPIO_DOUT]
	mov r3,#1
	lsl r3, r3, #9
	orr r2, r2, r3
	str r2, [r1, #GPIO_DOUT]
	
	
	
	ldr r1, gpio_pc_base_addr	
	ldr r2, [r1, #GPIO_MODEL]
	mov r3, #0x33333333
	orr r2, r2, r3
	str r2, [r1, #GPIO_MODEL]
	
	ldr r2, [r1, #GPIO_DOUT]
	mov r3, #0xff
	orr r2, r2, r3
	str r2, [r1, #GPIO_DOUT]
	
	
	gpio_pc_base_addr:
	.long GPIO_PC_BASE



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

