#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

 uint32_t x2 = 1;
 uint32_t teller=0;
 uint32_t delay=0;
 uint32_t buttons=0;
 uint32_t flag=0;



void __attribute__ ((interrupt)) TIMER1_IRQHandler(){
   *TIMER1_IFC=0x1;
  	teller++;
  	if(teller==delay){
  		*DAC0_CH0DATA = 0x000;
	    *DAC0_CH1DATA = 0x000;
	    flag=1;
	    disableDAC();
  	}
  	else{

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

void __attribute__ ((interrupt)) TIMER2_IRQHandler(){
   *TIMER2_IFC=0x1;
   	*DAC0_CH0DATA = 0x000;
     *DAC0_CH1DATA = 0x000;
     stopTimer1();
     //stopTimer2();
   	*GPIO_PA_DOUT=0xffff;
   //disableDAC();

}

void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler(){

   *GPIO_IFC=0xff;
   GPIO_interrupt();
   
      
   
}

void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler(){
   *GPIO_IFC=0xff;
   GPIO_interrupt();
}

void GPIO_interrupt(){
	*GPIO_PA_DOUT=(*GPIO_PC_DIN << 8);
	buttons=*GPIO_PC_DIN;
   if(buttons == 254){
   		setupDAC();
   		uint32_t freq=NOTE_D5;
	    setupTimer(14000000/(8*freq));
	    teller=0;
	    delay=200;
	    delay=delay*freq/1000;
   	}

   else if(buttons == 253){
   		setupDAC();
   		uint32_t freq=660;
	    setupTimer(14000000/(8*freq));
	    teller=0;
	    delay=200;
	    delay=delay*freq/1000;
   	}

   else if(buttons == 251){
   		setupDAC();
   		uint32_t freq=660;
	    setupTimer(14000000/(8*freq));
	    teller=0;
	    delay=200;
	    delay=delay*freq/1000;
   	}

   else if(buttons == 247){
   		setupDAC();
   		uint32_t freq=NOTE_AS5;
	    setupTimer(14000000/(8*freq));
	    teller=0;
	    delay=100;
	    delay=delay*freq/1000;
   	}

   else if(buttons == 239){
   		setupDAC();
   		uint32_t freq=NOTE_F3;
	    setupTimer(14000000/(8*freq));
	    teller=0;
	    delay=150;
	    delay=delay*freq/1000;
   	}

   	  else if(buttons == 223){
   		setupDAC();
   		struct tone gameover3[4]= {
		  {660,200},
		  {330,200},
		  {165,200},
		  {500,200} 
		};
   		playMusic(gameover3,4);
   		disableDAC();
   		/*
   		uint32_t freq=NOTE_C4;
	    setupTimer(14000000/(8*freq));
	    teller=0;
	    delay=200;
	    delay=delay*freq/1000;
	    freq=NOTE_E4;
	    
	    uint32_t counter=0;
	    /*
	    while(counter<1400000){
	    	counter++;
	    	
	    }
	    */
	    /*
	    TIMER1_IRQHandler();
	    setupTimer(14000000/(8*freq));
	    teller=0;
	    delay=500;
	    delay=delay*freq/1000;
	    
	    flag=0;
	    //while(flag==0){}
	    freq=NOTE_D4;
	    setupTimer(14000000/(8*freq));
	    teller=0;
	    delay=500;
	    delay=delay*freq/1000;
	    */
   	}




   		
      //setupTimer2(14000000/(8*200));
   

}

