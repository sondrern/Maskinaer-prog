#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

 uint32_t x2 = 1;
 uint32_t teller=0;
 uint32_t delay=0;
 uint32_t buttons=0;
 
 uint32_t iterator = 0;
 uint32_t lengde = 0;





void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler(){

   *GPIO_IFC=0xff;
   GPIO_interrupt();
   
      
   
}

void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler(){
   *GPIO_IFC=0xff;
   GPIO_interrupt();
}



void GPIO_interrupt(){
	setupDAC();
	
	*GPIO_PA_DOUT=(*GPIO_PC_DIN << 8);
	buttons=*GPIO_PC_DIN;
   if(buttons == 254){
   		
   		lengde=1;
		sounds[0].note=NOTE_D5;
		sounds[0].time=200;
   		
   		teller=0;
   		iterator=0;
   		play(iterator);
   	}

   else if(buttons == 253){
   		
   		lengde=1;
		sounds[0].note=660;
		sounds[0].time=200;
   		
   		teller=0;
   		iterator=0;
   		play(iterator);
   	}

   else if(buttons == 251){
   		
   		lengde=1;
		sounds[0].note=660;
		sounds[0].time=200;
   		
   		teller=0;
   		iterator=0;
   		play(iterator);
   	}

   else if(buttons == 247){
   		
	    
   		lengde=1;
		sounds[0].note=NOTE_AS5;
		sounds[0].time=100;
   		
   		teller=0;
   		iterator=0;
   		play(iterator);
   	}

   else if(buttons == 239){
   		
   		lengde=1;
		sounds[0].note=NOTE_F3;
		sounds[0].time=150;
   		
   		teller=0;
   		iterator=0;
   		play(iterator);
   	}

   	  else if(buttons == 223){
   		
   		lengde=5;
		sounds[0].note=660;
		sounds[1].note=330;
		sounds[2].note=165;
		sounds[3].note=500;
		sounds[4].note=100;

		sounds[0].time=200;
		sounds[1].time=200;
		sounds[2].time=200;
		sounds[3].time=200;
		sounds[4].time=600;
   		
   		teller=0;
   		iterator=0;
   		play(iterator);
   		//startTimer();
   	
   	}
  

   

}

void play(uint32_t a){
	//stopTimer();
	//startTimer();
	uint32_t freq=sounds[a].note;
	delay=sounds[a].time;

    delay=(delay*freq)/1000;
	setupLowEnergyTimer();
	changeTopCounter(freq);
  
    
   
}

void playStart(void){
		setupDAC();
   		lengde=7;
		sounds[0].note=400;
		sounds[1].note=500;
		sounds[2].note=600;
		sounds[3].note=700;
		sounds[4].note=600;
		sounds[5].note=500;
		sounds[6].note=400;

		sounds[0].time=200;
		sounds[1].time=200;
		sounds[2].time=200;
		sounds[3].time=200;
		sounds[4].time=200;
		sounds[5].time=200;
		sounds[6].time=200;
   		
   		teller=0;
   		iterator=0;
   		play(iterator);
}


void __attribute__ ((interrupt)) LETIMER0_IRQHandler(){
	
*LETIMER0_IFC = 1;
    teller++;

    

    if (teller==delay){
    	teller=0;
    	iterator++;
    	if(iterator>=lengde){
    		*DAC0_CH0DATA = 0x000;
		    *DAC0_CH1DATA = 0x000;
		   	disableLowEnergyTimer();
		    disableDAC();
		    
    	}
    	else{
    		play(iterator);
    	}

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