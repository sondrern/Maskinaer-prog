#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

/* function to setup the timer */
void setupTimer(uint16_t period)
{
	/*
	   TODO enable and set up the timer

	   1. Enable clock to timer by setting bit 6 in CMU_HFPERCLKEN0
	   2. Write the period to register TIMER1_TOP
	   3. Enable timer interrupt generation by writing 1 to TIMER1_IEN
	   4. Start the timer by writing 1 to TIMER1_CMD

	   This will cause a timer interrupt to be generated every (period) cycles. Remember to configure the NVIC as well, otherwise the interrupt handler will not be invoked.
	 */
	   *CMU_HFPERCLKEN0 |= CMU2_HFPERCLKEN0_TIMER1;	//Enable clock
	     
	   *TIMER1_TOP = period;		// Period to register
	   *TIMER1_IEN=0x1; 		  //Enable timer interrupt generation
	   *ISER0 |= 0xc;  			 // Enable timer interrupts
	  // *TIMER1_CMD=0x1; 		// Start the timer

}

void startTimer(){
	*TIMER1_CMD = 0x1;
}

void stopTimer(){
	*TIMER1_CMD = 0x0;
}

void disableTimer(){
	*CMU_HFPERCLKEN0 &= ~CMU2_HFPERCLKEN0_TIMER1;
	*TIMER1_IEN =0x0;
}