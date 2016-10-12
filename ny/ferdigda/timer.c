#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#define RTC_clock 32768



void

/*Purpose:Turns on the low-energy(LE) timer by enabling the ocscillator. It also enables the clock for the LE timer and the top counter value for the timer. The to last lines enables the interrupt generation and starts the timer
Arguments:void
Returns:void

*/
LEtimerON ()
{
  *CMU_OSCENCMD = (1 << 6);
  *CMU_HFCORECLKEN0 |= (1 << 4);
  *LETIMER0_CTRL |= (1 << 9);
  *CMU_LFACLKEN0 |= (1 << 2);
  *LETIMER0_TOP = 1;
  *LETIMER0_IEN = 1;
  *LETIMER0_CMD = 1;

}


/*Purpose: Change the top counter value by passing a frequency
 Arguments: the sample_rate which we want to change to.
 Returns: void.



*/
void
SetLEtimer (int freq)
{
  *LETIMER0_TOP = (RTC_clock) / freq;
}


void

/*Purpose:Turns off the low-energy(LE) timer by disabling the ocscillator and initializing all the values to zero.
Arguments:void
Returns:void

*/
LEtimerOFF ()
{
  *CMU_OSCENCMD &= ~(1 << 6);
  *CMU_HFCORECLKEN0 &= (1 << 4);
  *LETIMER0_CTRL &= (1 << 9);
  *CMU_LFACLKEN0 &= (1 << 2);
  *LETIMER0_TOP = 0;
  *LETIMER0_IEN = 0;
  *LETIMER0_CMD = 0;
}
