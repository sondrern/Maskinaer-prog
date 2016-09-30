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
//void setupTimer(uint32_t period);
//void setupDAC();
void setupNVIC();
//void playMusic(void);


struct tone GAMEOVER[5] = {
{NOTE_C4,500},
{0,200},
{NOTE_E4,500},
{0,200},
{NOTE_D4,500},
};
//void playMusic(struct tone test[], uint32_t lengde);
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

struct tone start2[7] = {
   {400,200},
  
   {500, 200},
   
   {600, 200},
   
   {700, 200},
   
   {600, 200},
   
   {500, 200},
   
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

	//setupNVIC();

      *GPIO_PA_DOUT = 0xff00;
      //
      playMusic(start2,7);
      setupNVIC();
      disableDAC();
   
	while (1){


   }

	return 0;
}

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
            if (teller==((delay*freq)/1000)) {
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

void playMusic(struct tone test[], uint32_t lengde)
{
   //setupDAC();
   for (int j=0; j<lengde; j++){
      playTone(test[j].note, test[j].time);
   }
   //disableDAC();
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
