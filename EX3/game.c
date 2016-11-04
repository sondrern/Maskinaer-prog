#include "frame.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
	printf("Hello World, I'm game!\n");
	init_game();
	/*
	while(1){
		updategame();
		usleep(50000);
	}
	*/
	//////// GAMEPAD TEST ///////////////
	
	FILE *driver;
	driver = fopen("/dev/gamepad", "rb");
	if(driver==NULL){
		printf("dev/gamepad IS NOT A DIRECTORY\n");
		exit(0);
	}
	while(1){
		int *ppos = NULL;
		//loff_t (*llseek) (driver, ppos, int);
		char buf[0];
		read_gamepad(driver, buf, 1, ppos);
		printf("Buttons = %i \n", buf);
		usleep(1000000);
	}
	
	
	exit(EXIT_SUCCESS);
}

