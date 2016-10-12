#include <stdint.h>
#include <stdbool.h>
#include "efm32gg.h"


void
setupTimer (uint16_t period)
{
 
  *CMU_HFPERCLKEN0 |= CMU2_HFPERCLKEN0_TIMER1;	

  *TIMER1_TOP = period;
  *TIMER1_IEN = 0x1;
  *ISER0 |= 0xc;	
  *TIMER1_CMD = 0x1;

}

void
startTimer ()
{
  *TIMER1_CMD = 0x1;
}

void
stopTimer ()
{
  *TIMER1_CMD = 0x0;
}

void
disableTimer ()
{
  *CMU_HFPERCLKEN0 &= ~CMU2_HFPERCLKEN0_TIMER1;
  *TIMER1_IEN = 0x0;
}
