#include <stdint.h>
#include <stdbool.h>
#include "efm32gg.h"
#define   SAMPLE_PERIOD   0


struct tone
{
  int note, time;
};

struct tone gameover2[4] = {
  {660, 200},
  {330, 200},
  {165, 200},
  {500, 200}
};

void setupGPIO ();
void setupTimer (uint16_t period);
void setupDAC ();
void polling();
void playMusic(struct tone test[], uint32_t lengde);


int main (void)
{

  setupGPIO ();
  setupDAC ();

  *GPIO_PA_DOUT = 0xff00;
  playMusic(gameover2, 4);





  while (1)
    {
  polling();
    }

  return 0;
}




void
playTone (uint32_t tone, uint32_t delay)
{
  uint32_t freq = tone;
  uint32_t x2 = 1;
  uint32_t teller = 0;
  uint32_t x = 0;
  uint32_t conter;
  if (tone == 0)
    {
      conter = 14000000 / (8 * 1000);
      setupTimer (conter);
      while (1)
	{
	  x = *TIMER1_CNT;
	  if (x == conter)
	    {
	      teller++;
	      if (teller == delay)
		{
		  *DAC0_CH0DATA = 0x000;
		  *DAC0_CH1DATA = 0x000;
		  return;
		}
	    }
	}
    }
  else
    {
      conter = 14000000 / (8 * freq);
      setupTimer (conter);
    }


  while (1)
    {
      x = *TIMER1_CNT;
      if (x == conter)
	{
	  teller++;
	  if (teller == ((delay * freq) / 1000))
	    {
	      *DAC0_CH0DATA = 0x000;
	      *DAC0_CH1DATA = 0x000;
	      return;
	    }
	  if (x2)
	    {
	      *DAC0_CH0DATA = 0xfff;
	      *DAC0_CH1DATA = 0xfff;
	      x2 = 0;
	    }
	  else
	    {

	      *DAC0_CH0DATA = 0x000;
	      *DAC0_CH1DATA = 0x000;
	      x2 = 1;
	    }


	}
    }

}




void playMusic(struct tone test[], uint32_t lengde)
{
  for (int j = 0; j < lengde; j++)
    {
      playTone (test[j].note, test[j].time);
    }
}



/*
Purpose: Poll the four buttons and play the coresponding sound if a buttons i getting pushed. 
Argument: void
returns: void.



*/
void polling(){
	 int buttons;
      buttons = *GPIO_PC_DIN;
      *GPIO_PA_DOUT = (*GPIO_PC_DIN << 8);

      if (buttons == button1)
	{

	  setupDAC ();
	  playTone (220, 100);
	  disableDAC ();
	}




      else if (buttons == button2)
	{
	  setupDAC ();
	  playTone (261, 200);
	  disableDAC ();
	}

      else if (buttons == button3)
	{
	  setupDAC ();
	  playTone (293, 200);
	  disableDAC ();
	}

      else if (buttons == button4)
	{

	  setupDAC ();
	  playTone (550, 200);
	  disableDAC ();
	}





}







