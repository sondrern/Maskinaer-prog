#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"




/*Purpose: Enable the DAC by:
1. Setting the bit 17 in CMU_HPERCLKEN0 to 1
2.  Presscaling the DAC clock by writing to the DAC0_CTRL, and setting it to a sample hold modus
3.  Enable both DAC channels: DAC0_CH1CTRL and DAC0_CH0CTRL
Argument: void
Returns: void
*/
void setupDAC ()
{

  *CMU_HFPERCLKEN0 |= CMU2_HFPERCLKEN0_DAC0;

  *DAC0_CTRL = 0x50014;
  *DAC0_CH1CTRL = 0x1;
  *DAC0_CH0CTRL = 0x1;

}


/*Purpose: Disable the DAC by initializing the registers to 0
Argument: void
Returns: void
*/
void
disableDAC ()
{

  *DAC0_CTRL = 0;
  *DAC0_CH1CTRL = 0;
  *DAC0_CH0CTRL = 0;
  *CMU_HFPERCLKEN0 &= ~CMU2_HFPERCLKEN0_DAC0;
}
