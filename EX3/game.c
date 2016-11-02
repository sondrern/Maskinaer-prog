#include "frame.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
	printf("Hello World, I'm game!\n");
	frame_init();
	testscreen();
	
	//////// GAMEPAD TEST ///////////////
	
	FILE *driver;
	driver = fopen("/dev/gamepad", "rb");
	while(1){
		int *ppos = NULL;
		//loff_t (*llseek) (driver, ppos, int);
		char buf[0];
		read_gamepad(driver, buf, 1, ppos);
		printf("Buttons = %i \n", buf);
		// DELAY !!!!!
	}
	exit(EXIT_SUCCESS);
}
/*
#include "frame.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
	printf("Hello World, I'm game!\n");
	frameinit();
 drawrectangle(160,120,50,50);
	exit(EXIT_SUCCESS);
}

*/
