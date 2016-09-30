#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

/* 
  TODO calculate the appropriate sample period for the sound wave(s) 
  you want to generate. The core clock (which the timer clock is derived
  from) runs at 14 MHz by default. Also remember that the timer counter
  registers are 16 bits.
*/
/* The period between sound samples, in clock cycles */
#define   SAMPLE_PERIOD   0

/* Declaration of peripheral setup functions */
void setupGPIO();
void setupTimer(uint32_t period);
void setupDAC();
void setupNVIC();
//void playMusic(void);

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

struct tone{
   int note, time;
};
struct tone GAMEOVER[5] = {
{NOTE_C4,500},
{0,200},
{NOTE_E4,500},
{0,200},
{NOTE_D4,500},
};
void playMusic(struct tone test[], uint32_t lengde);
struct tone gameover2[4]= {
  {660,200},
  {330,200},
  {165,200},
  {500,200} 
};


struct tone mario[218] = {
   {660,210},
   {0,14},
   {660,200},
   {0,14},
   {660,210},
   {0,100},
   {510,210},
   {0,14},
   {660,210},
   {0,14},
   {770,210},
   {0,171},
   {380,210},
   {0,285},
   {510,210},
   {0,142},
   {380,210},
   {0,142},
   {320,210},
   {0,71},
   {440,210},
   {0,42},
   {480,168},
   {0,42},
   {450,210},
   {0,42},
   {430,210},
   {0,171},
   {380,210},
   {0,71},
   {660,168},
   {0,28},
   {760,105},
   {0,21},
   {860,210},
   {0,57},
   {700,168},
   {0,21},
   {760,105},
   {0,28},
   {660,168},
   {0,28},
   {520,168},
   {0,71},
   {580,168},
   {0,21},
   {480,168},
   {0,128},
   {510,210},
   {0,64},
   {380,210},
   {0,57},
   {320,210},
   {0,71},
   {440,210},
   {0,42},
   {480,168},
   {0,47},
   {450,210},
   {0,21},
   {430,210},
   {0,42},
   {380,210},
   {0,28},
   {660,168},
   {0,28},
   {760,105},
   {0,21},
   {860,210},
   {0,42},
   {700,168},
   {0,21},
   {760,105},
   {0,50},
   {660,168},
   {0,42},
   {520,168},
   {0,21},
   {580,168},
   {0,21},
   {480,168},
   {0,128},
   {500,210},
   {0,114},
   {760,210},
   {0,14},
   {720,210},
   {0,21},
   {680,210},
   {0,21},
   {620,315},
   {0,85},
   {650,315},
   {0,42},
   {380,210},
   {0,21},
   {430,210},
   {0,57},
   {500,210},
   {0,42},
   {430,210},
   {0,21},
   {500,210},
   {0,14},
   {570,210},
   {0,64},
   {500,210},
   {0,64},
   {760,210},
   {0,14},
   {720,210},
   {0,21},
   {680,210},
   {0,21},
   {620,315},
   {0,57},
   {650,420},
   {0,57},
   {1020,168},
   {0,42},
   {1020,168},
   {0,21},
   {1020,168},
   {0,57},
   {380,210},
   {0,42},
   {500,210},
   {0,57},
   {760,210},
   {0,14},
   {720,210},
   {0,21},
   {680,210},
   {0,21},
   {620,315},
   {0,71},
   {650,315},
   {0,42},
   {380,210},
   {0,21},
   {430,210},
   {0,57},
   {500,210},
   {0,42},
   {430,210},
   {0,21},
   {500,210},
   {0,14},
   {570,210},
   {0,60},
   {585,210},
   {0,64},
   {550,210},
   {0,60},
   {500,210},
   {0,71},
   {380,210},
   {0,42},
   {500,210},
   {0,42},
   {500,210},
   {0,42},
   {500,210},
   {0,21},
   {580,168},
   {0,50},
   {660,168},
   {0,21},
   {500,168},
   {0,42},
   {430,168},
   {0,21},
   {380,168},
   {0,85},
   {500,126},
   {0,21},
   {500,168},
   {0,42},
   {500,126},
   {0,50},
   {500,168},
   {0,21},
   {580,168},
   {0,21},
   {660,168},
   {0,107},
   {500,126},
   {0,21},
   {500,168},
   {0,42},
   {500,126},
   {0,50},
   {500,168},
   {0,21},
   {580,168},
   {0,50},
   {660,168},
   {0,21},
   {500,168},
   {0,42},
   {430,168},
   {0,21},
   {380,168},
   {0,114},
   {660,210},
   {0,21},
   {660,210},
   {0,42},
   {660,210},
   {0,42},
   {510,210},
   {0,14},
   {660,210},
   {0,42},
   {770,210},
   {0,78},
   {380,210},
   {0,82},
};
/*
struct tone start[12] = {
   {NOTE_C4,200},
   {0,25},
   {NOTE_D4, 200},
   {0,25},
   {NOTE_E4, 200},
   {0,25},
   {NOTE_F4, 200},
   {0,25},
   {NOTE_A4, 200},
   {0,25},
   {NOTE_B4, 200},
   {0,25},
   {NOTE_C4, 200},
   

};
*/
struct tone start[12] = {
   {400,200},
   {0,25},
   {500, 200},
   {0,25},
   {600, 200},
   {0,25},
   {700, 200},
   {0,25},
   {600, 200},
   {0,25},
   {500, 200},
   {0,25},
   {400, 200},
   

};

struct tone hit[1] = {
   {660,200}
   

};

struct tone buttonpress[1] = {
   {NOTE_D5,75}
};

struct tone enter[1] = {
   {NOTE_AS5,100}

};

struct tone back[1] = {
   {NOTE_F3,150}

};




 


/* Your code will start executing here */
int main(void)
{
	/* Call the peripheral setup functions */
	setupGPIO();
	setupDAC();

	setupNVIC();

      *GPIO_PA_DOUT = 0xff00;
      playMusic(gameover2,4);
   

      /*
      playTone(220, 1);
      playTone(261, 2);
      playTone(293,2);
      playTone(550, 2);
      */
	while (1){


   }

	return 0;
}
/*
void playTone(uint32_t tone, uint32_t delay){
   uint32_t freq=tone;
   uint32_t x2 = 1;
   uint32_t teller=0;
   uint32_t x =0;
   uint32_t conter;
   //delay=delay*2;
   if(tone==0){ 
      conter = 14000000/(8*1000);
      setupTimer(conter);
      while(1){
         x = *TIMER1_CNT;
               if(x==conter){
            teller++;
            if (teller==delay){
                  *DAC0_CH0DATA = 0x000;
                  *DAC0_CH1DATA = 0x000;
                  return;
            }
      }
   }
}
      else{
         conter = 14000000/(8*freq);
         setupTimer(conter);

      }
      
      
      while(1){
         x = *TIMER1_CNT;
                  if(x==conter){
               teller++;
               if (teller==((delay*freq)/1000)){
                     *DAC0_CH0DATA = 0x000;
                     *DAC0_CH1DATA = 0x000;
                     return;
               }
            if(x2){
               *DAC0_CH0DATA = 0xfff;
               *DAC0_CH1DATA = 0xfff;
               x2=0;
            }
            else{
               
                 *DAC0_CH0DATA = 0x000;
               *DAC0_CH1DATA = 0x000;
               x2=1; 
               
               
            }

             
         }
      }

}
*/

void playTone(uint32_t tone, uint32_t delay){
   uint32_t freq=tone;
   uint32_t x2 = 1;
   uint32_t teller=0;
   uint32_t x =0;
   uint32_t conter;
   //delay=delay*2;
   if(tone==0){ 
      conter = 14000000/(8*1000);
      setupTimer(conter);
      while(1){
         _asm(WFI);
            teller++;
            if (teller==delay){
                  *DAC0_CH0DATA = 0x000;
                  *DAC0_CH1DATA = 0x000;
                  return;
            }
      
      }
   }
      else{
         conter = 14000000/(8*freq);
         setupTimer(conter);

      }
      
      
      while(1){
            _asm(WFI);
               teller++;
               if (teller==((delay*freq)/1000)){
                     *DAC0_CH0DATA = 0x000;
                     *DAC0_CH1DATA = 0x000;
                     return;
               }
            if(x2){
               *DAC0_CH0DATA = 0xfff;
               *DAC0_CH1DATA = 0xfff;
               x2=0;
            }
            else{
               
                 *DAC0_CH0DATA = 0x000;
               *DAC0_CH1DATA = 0x000;
               x2=1; 
               
               
            }

             
         
      }

}

void playMusic(struct tone test[], uint32_t lengde)
{
   for (int j=0; j<lengde; j++){
      playTone(test[j].note, test[j].time);
   }
}
  


void setupNVIC()
{
	/* TODO use the NVIC ISERx registers to enable handling of interrupt(s)
	   remember two things are necessary for interrupt handling:
	   - the peripheral must generate an interrupt signal
	   - the NVIC must be configured to make the CPU handle the signal
	   You will need TIMER1, GPIO odd and GPIO even interrupt handling for this
	   assignment.
	 */
      *ISER0=0x1802;
}

void _attribute_ ((interrupt)) TIMER1_IRQHandler(){
   *TIMER1_IFC=1;


}

void _attribute_ ((interrupt)) GPIO_EVEN_IRQHandler(){

   *GPIO_IFC=0xff;
   *GPIO_PA_DOUT=(*GPIO_PC_DIN << 8);
}

void _attribute_ ((interrupt)) GPIO_ODD_IRQHandler(){
   *GPIO_IFC=0xff;
   *GPIO_PA_DOUT=(*GPIO_PC_DIN << 8);
}


/* if other interrupt handlers are needed, use the following names: 
   NMI_Handler
   HardFault_Handler
   MemManage_Handler
   BusFault_Handler
   UsageFault_Handler
   Reserved7_Handler
   Reserved8_Handler
   Reserved9_Handler
   Reserved10_Handler
   SVC_Handler
   DebugMon_Handler
   Reserved13_Handler
   PendSV_Handler
   SysTick_Handler
   DMA_IRQHandler
   GPIO_EVEN_IRQHandler
   TIMER0_IRQHandler
   USART0_RX_IRQHandler
   USART0_TX_IRQHandler
   USB_IRQHandler
   ACMP0_IRQHandler
   ADC0_IRQHandler
   DAC0_IRQHandler
   I2C0_IRQHandler
   I2C1_IRQHandler
   GPIO_ODD_IRQHandler
   TIMER1_IRQHandler
   TIMER2_IRQHandler
   TIMER3_IRQHandler
   USART1_RX_IRQHandler
   USART1_TX_IRQHandler
   LESENSE_IRQHandler
   USART2_RX_IRQHandler
   USART2_TX_IRQHandler
   UART0_RX_IRQHandler
   UART0_TX_IRQHandler
   UART1_RX_IRQHandler
   UART1_TX_IRQHandler
   LEUART0_IRQHandler
   LEUART1_IRQHandler
   LETIMER0_IRQHandler
   PCNT0_IRQHandler
   PCNT1_IRQHandler
   PCNT2_IRQHandler
   RTC_IRQHandler
   BURTC_IRQHandler
   CMU_IRQHandler
   VCMP_IRQHandler
   LCD_IRQHandler
   MSC_IRQHandler
   AES_IRQHandler
   EBI_IRQHandler
   EMU_IRQHandler
*/
