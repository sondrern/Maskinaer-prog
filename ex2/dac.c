#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

void setupDAC()
{
	/*
	    TODO enable and set up the Digital-Analog Converter

	   1. Enable the DAC clock by setting bit 17 in CMU_HFPERCLKEN0
	   2. Prescale DAC clock by writing 0x50010 to DAC0_CTRL
	   3. Enable left and right audio channels by writing 1 to DAC0_CH0CTRL and DAC0_CH1CTRL
	   4. Write a continuous stream of samples to the DAC data registers, DAC0_CH0DATA and DAC0_CH1DATA, for example from a timer interrupt
	 */
	   *CMU_HFPERCLKEN0 |= CMU2_HFPERCLKEN0_DAC0; // Enable DAC clock
	   *DAC0_CTRL = 0x50014;						//Prescale DAC clock
	   //*DAC0_CTRL |= (1 << 1);
	   *DAC0_CH1CTRL = 0x1;							//Enable left and right audio channels
	   *DAC0_CH0CTRL = 0x1;

}

void disableDAC{

	   *DAC0_CTRL = 0;						//Prescale DAC clock
	   //*DAC0_CTRL |= (1 << 1);
	   *DAC0_CH1CTRL = 0;							//Enable left and right audio channels
	   *DAC0_CH0CTRL = 0;
	   *CMU_HFPERCLKEN0 &= ~CMU2_HFPERCLKEN0_DAC0; // Enable DAC clock
}