#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"



void
setupGPIO ()
{



  *CMU_HFPERCLKEN0 |= CMU2_HFPERCLKEN0_GPIO;
  *GPIO_PA_CTRL = 2;
  *GPIO_PA_MODEH = 0x55555555;



  *GPIO_PC_MODEL = 0x33333333;
  *GPIO_PC_DOUT = 0xff;


  *GPIO_EXTIPSELL = 0x22222222;	
  *GPIO_EXTIRISE = 0xff;
  *GPIO_EXTIFALL = 0xff;
  *GPIO_IEN = 0xff;
}
