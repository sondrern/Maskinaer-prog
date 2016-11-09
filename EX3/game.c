
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

uint16_t nr11[] = {
	BLACK, WHITE, WHITE, BLACK, BLACK,
	BLACK, WHITE, WHITE, BLACK, BLACK,
	BLACK, WHITE, WHITE, BLACK, BLACK,
	BLACK, BLACK, WHITE, BLACK, BLACK,
	BLACK, BLACK, WHITE, BLACK, BLACK,
	BLACK, BLACK, WHITE, BLACK, BLACK,
	BLACK, BLACK, WHITE, BLACK, BLACK,
	BLACK, BLACK, WHITE, BLACK, BLACK,
	BLACK, BLACK, WHITE, BLACK, BLACK,
	BLACK, BLACK, WHITE, BLACK, BLACK,
	BLACK, BLACK, WHITE, BLACK, BLACK,
	BLACK, BLACK, WHITE, BLACK, BLACK,
	BLACK, BLACK, WHITE, BLACK, BLACK,
	BLACK, BLACK, WHITE, BLACK, BLACK,
	BLACK, WHITE ,WHITE, WHITE, BLACK,
	BLACK, WHITE, WHITE, WHITE, BLACK
};

 char two[] = {
'W','W', 'W',
'X','X', 'W',
'X','X', 'W',
'W','W', 'W',
'W','X', 'X',
'W','X', 'X',
'W','X', 'X',
'W','W', 'W',
};


#define bufferlen 8
FILE *driver;
void init_gamepad(void);
void menu(void);

int main(int argc, char *argv[])
{
	system("echo 0 > /sys/class/graphics/fbcon/cursor_blink");
	init_gamepad();
	init_game();
	int level=1;
	


	//draw_array(nr11);
	//draw_text2(two);
	//usleep(10000000);  	



	int button;
	while(1){
		button = ((int)getc(driver));
		if (button==254){
			menu();
		}
		else{
			updategame(button);
		}
		//printf("Button = %i \n", button);
		if(level==0){
			usleep(30000);
		}
		else if(level==1){
			usleep(10000);
		}
	}
	

	
	
	exit(EXIT_SUCCESS);
}

void menu(void){
	testscreen();
	system("clear");
	printf("Main menu \n");
	while(1){
		int button = ((int)getc(driver));
		if(button==254){
			usleep(1000000);
			return;
		}
		usleep(30000);
	}
}

void init_gamepad(void){
	system("modprobe driver-gamepad");
	driver = fopen("/dev/gamepad", "rb");

	if(driver==NULL){
		printf("dev/gamepad IS NOT A DIRECTORY\n");
		exit(0);
	}
}

