#include <stdio.h>
#include <stdlib.h>
#include "frame.h"

int main(int argc, char *argv[])
{
	printf("Hello World, I'm game!\n");
	initDisplay();
//	draw_text(intro);
//	refresh_screen();
	
	draw_rect(10, 10, 0xFFFF);
	refresh_screen();
	
	
	
	
	//return 0;
	exit(EXIT_SUCCESS);
}
