
#ifndef _POSIX_C_SOURCE 
#define _POSIX_C_SOURCE 1
#define _GNU_SOURCE 1
#endif

#include <stdio.h>
#include <stdlib.h>
#include "frame.h"
//#include "font.h"
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>


#define bufferlen 8

void init_gamepad(void);


int main(int argc, char *argv[])
{
	system("echo 0 > /sys/class/graphics/fbcon/cursor_blink");
	init_gamepad();
	init_game();
	menu();
	
  	



	int button;
	while(1){
		button = ((int)getc(driver));
		
		if (button==254){
			menu();
		}
		else{
			gameon=1;
			updategame(button);
		}
		//printf("Button = %i \n", button);
		
		
		
		usleep(50);
	}
	

	
	
	exit(EXIT_SUCCESS);
}



void init_gamepad(void){
	system("modprobe driver-gamepad");
	driver = fopen("/dev/gamepad", "rb");

	if(driver==NULL){
		printf("dev/gamepad IS NOT A DIRECTORY\n");
		exit(0);
	}
}

