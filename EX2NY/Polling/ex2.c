#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#define   SAMPLE_PERIOD   0
void setupGPIO ();
void setupTimer (uint32_t period);
void setupDAC ();


#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

struct tone
{
  int note, time;
};


void playMusic (struct tone test[], uint32_t lengde);
struct tone gameover2[4] = {
  {660, 200},
  {330, 200},
  {165, 200},
  {500, 200}
};




struct tone start[12] = {
  {400, 200},
  {0, 25},
  {500, 200},
  {0, 25},
  {600, 200},
  {0, 25},
  {700, 200},
  {0, 25},
  {600, 200},
  {0, 25},
  {500, 200},
  {0, 25},
  {400, 200},


};









int
main (void)
{

  setupGPIO ();
  setupDAC ();

  *GPIO_PA_DOUT = 0xff00;
  playMusic (gameover2, 4);




  int buttons;

  while (1)
    {

      buttons = *GPIO_PC_DIN;
      *GPIO_PA_DOUT = (*GPIO_PC_DIN << 8);

      if (buttons == 254)
	{

	  setupDAC ();
	  playTone (220, 100);
	  disableDAC ();
	}




      else if (buttons == 253)
	{
	  setupDAC ();
	  playTone (261, 200);
	  disableDAC ();
	}

      else if (buttons == 251)
	{
	  setupDAC ();
	  playTone (293, 200);
	  disableDAC ();
	}

      else if (buttons == 247)
	{

	  setupDAC ();
	  playTone (550, 200);
	  disableDAC ();
	}
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




void
playMusic (struct tone test[], uint32_t lengde)
{
  for (int j = 0; j < lengde; j++)
    {
      playTone (test[j].note, test[j].time);
    }
}
