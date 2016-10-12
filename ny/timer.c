#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#define RTC_clock 32768



void
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



void
SetLEtimer (int sample_rate)
{
  *LETIMER0_TOP = (RTC_clock) / sample_rate;
}


void
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
