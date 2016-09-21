#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

/* function to set up GPIO mode and interrupts*/
void setupGPIO()
{
		/* TODO set input and output pins for the joystick */

	
	*CMU_HFPERCLKEN0 |= CMU2_HFPERCLKEN0_GPIO;	/* enable GPIO clock */
	*GPIO_PA_CTRL = 2;	/* set high drive strength */
	*GPIO_PA_MODEH = 0x55555555;	/* set pins A8-15 as output */



	*GPIO_PC_MODEL = 0x33333333; //sets pins c0 -7 as input
	*GPIO_PC_DOUT = 0xff; // enable internal pullup


	*GPIO_EXTIPSELL = 0x22222222; //Enable interrupts on port c (low register)
	*GPIO_EXTIRISE = 0xff; //Rising edge trigger enabled
	*GPIO_EXTIFALL = 0xff; //Falling edge trigger enabled
	*GPIO_IEN = 0xff; //external interrupt enabled
}
