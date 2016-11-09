
#ifndef _POSIX_C_SOURCE 
#define _POSIX_C_SOURCE 1
#define _GNU_SOURCE 1
#endif

#include <stdio.h>
#include <stdlib.h>
#include "frame.h"
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

#define bufferlen 8
FILE *driver;

int main(int argc, char *argv[])
{
	printf("Hello World, I'm game!\n");
	//init_game();
	/*
	while(1){
		updategame();
		usleep(50000);
	}
	*/
	//////// GAMEPAD TEST ///////////////
	
	system("modprobe driver-gamepad");
	driver = fopen("/dev/gamepad", "rb");

	if(driver==NULL){
		printf("dev/gamepad IS NOT A DIRECTORY\n");
		exit(0);
	}
	while(1){
	
		int button = ((int)getc(driver));
		printf(" Buttons = %i \n", button);
		
	/*
		char buf[bufferlen];
		getchar();			 
	    printf("Reading from the device...\n");
	    int ret = read(driver, buf, bufferlen);        // Read the response from the LKM
	   if (ret < 0){
		  perror("Failed to read the message from the device.");
	   }
	   printf("The received message is: [%s]\n", buf);
		*/	   
			   
		usleep(1000000);
	}
	
	
	exit(EXIT_SUCCESS);
}
