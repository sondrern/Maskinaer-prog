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

  *SCR = 6;
  __asm ("WFI");

  while (1)
    {


    }

  return 0;
}



void
setupNVIC ()
{

  *ISER0 = 0x4000802;
}
