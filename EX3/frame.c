#include "frame.h"
#include <linux/fb.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>


void frameinit(void){
	//map arrayet framebuffer til minne slik at vi kan skrive direkte med C kode.
	fd=0;
	rect.dx=0;
	rect.dy=0;
	rect.width= WIDTH;
	rect.height= HEIGTH;

	int frame_size= WIDTH*HEIGTH*2;


 	openfile();
	framebuffer = (uint16_t*)mmap( NULL,frame_size, PROT_READ | PROT_WRITE, MAP_SHARED,fd, 0);


	closefile(fd);




}

void openfile(void){
	fd= fopen("dev/fb0", O_DIRECTORY);
	if(!fd){

		printf("dev/fb0 IS NOT A DIRECTORY\n");
		exit(0);
	}
	print("file open\n");


}

void closefile(int fd){
	ioctl(fd,0x4680,&rect) ;
	printf("file refreshed\n");


	int a = close(fd); 
	if(a == -1){
		printf("Failed to close file\n");
		exit(0);
	}
	printf("filed closed\n");
}


int main()
{

return 0;



}
