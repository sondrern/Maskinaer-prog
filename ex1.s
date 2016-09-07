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
