#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"


#define   SAMPLE_PERIOD   0


void setupGPIO ();


void setupNVIC ();




int
main (void)
{

  setupGPIO ();
  setupDAC ();
  *GPIO_PA_DOUT = 0xff00;

  setupNVIC ();
  playStart ();
//Go to low energy sleep modus, wake up if interruption is detected
  *SCR = 6;
  __asm ("WFI");

  while (1)
    {


    }

  return 0;
}

/*Purpose:Enable the interrupt handling for Low Energy Timer, Timer1, Even GPIO, Odd GPIO
 Arguments:void
 returns: void */

void setupNVIC ()
{

  *ISER0 = 0x4000802;
}
