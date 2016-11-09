#include "frame.h"
#include <linux/fb.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>

#include <stdint.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <math.h>

int fd;
int frame_size;
void frameinit(void){
	//map arrayet framebuffer til minne slik at vi kan skrive direkte med C kode.

	rect.dx=0;
	rect.dy=0;
	rect.width= WIDTH;
	rect.height= HEIGTH;

	frame_size= WIDTH*HEIGTH*2;
 	fd= open("/dev/fb0",O_RDWR);
	if(!fd){

		printf("dev/fb0 IS NOT A DIRECTORY\n");
		exit(0);
	}

	printf("file open\n");
	framebuffer = (uint16_t*)mmap( NULL,frame_size, PROT_READ | PROT_WRITE, MAP_SHARED,fd, 0);

	for(int i=0;i<WIDTH*HEIGTH;i++)
	{
		framebuffer[i]= 0;
	}



}



void closefile(void){


	
	ioctl(fd,0x4680,&rect);
	printf("file refreshed\n");


	int a = close(fd); 
	if(a == -1){
		printf("Failed to close file\n");
		exit(0);
	}
	printf("filed closed\n");

}


void testscreen(void){

	for(int i=0;i<WIDTH*HEIGTH; i++)
	{
		framebuffer[i]=BLACK;
		//0b0000000000011111;
	}
	ioctl(fd,0x4680,&rect);
}






void drawrectangle(int column, int row,int rec_width,int rec_heigth, int color)
{	
	for(int i = column; i < column + rec_width; i++)
	{
		for(int j = row; j < row + rec_heigth; j++)
		{
			framebuffer[i + j * WIDTH] = color;
		}
	}
	
}

void refresh_screen(void){
	ioctl(fd,0x4680,&rect);
}


void compute_slope(void){
	
	/*
	if(current_x == LEFT || current_x == RIGTH){		
		// Goalcurr
		printf("GOAL");
		init_game();
	}
	*/	
	
	if(current_y>=r_paddle_y && current_y<=r_paddle_y+PADDLEHEIGTH){
		//printf("Y dir r Paddle = ball y");
		if(current_x >= RIGTH-(PADDLEWIDTH*2)){
			dx = 0 - dx;
			printf("Rightpaddle hit! \n");
		}
	
	}
	
	else{
		if(current_x >= RIGTH-(PADDLEWIDTH*2)){
			score1=score1+1;
			printf("Score 1 = %i, Score2 = %i \n", score1, score2);
			goal();
		}
	
	}	
	
	
	if(current_y+BALLSIZE>=l_paddle_y && current_y<=l_paddle_y+PADDLEHEIGTH){
		//printf("Y dir left Paddle = ball y");
		if(current_x <= LEFT+PADDLEWIDTH){
			dx = 0 - dx;
			printf("Leftpaddle hit! \n");
		}
	
	}
	
	else{
		if(current_x <= LEFT+PADDLEWIDTH){
			score2=score2+1;
			printf("Score 1 = %i, Score2 = %i \n", score1, score2);
			goal();
		}
	
	}	
	
	
	if((current_y <= (TOP+5))) {
		dy = 0 - dy;
		printf("Top hit! \n");
	
	}
	if(current_y >= (BUTTOM-15)) {
		dy = 0 - dy;
		printf("Buttom hit! \n");
	}
	
}

void updategame(void){
	
	last_x = current_x + dx;
	current_x = current_x + dx;
	
	last_y = current_y + dy;
	current_y = current_y + dy;
	
	l_paddle_y = l_paddle_y + left_dy;
	// Define boundries for paddle top and buttom etc
	r_paddle_y = r_paddle_y + right_dy;
	
	// Update ball pos @ display
	drawrectangle(last_x-dx, last_y-dy, BALLSIZE, BALLSIZE, BLACK);
	drawrectangle(current_x, current_y, BALLSIZE, BALLSIZE, WHITE);
	
	// Update left paddle pos @ display
	drawrectangle(l_paddle_x, l_paddle_y, PADDLEWIDTH, PADDLEHEIGTH, WHITE);
	drawrectangle(l_paddle_x, l_paddle_y-left_dy, PADDLEWIDTH, left_dy, BLACK);
		
	
	// Update rigth paddle pos @ display
	drawrectangle(r_paddle_x, r_paddle_y, PADDLEWIDTH, PADDLEHEIGTH, WHITE);
	drawrectangle(r_paddle_x, r_paddle_y-right_dy, PADDLEWIDTH, right_dy, BLACK);
	
	refresh_screen();	
	compute_slope();
}



void init_game(void){
	frameinit();
	testscreen();
	current_x = 150;
	current_y = 110;
	last_x = 150;
	last_y = 110;
	
	dy = 10;
	dx = 10;
	
	l_paddle_x=0;
	l_paddle_y=95;
	
	r_paddle_x=310;
	r_paddle_y = 160;

	left_dy=0;
	right_dy = 0;
	
	score1=0;
	score2=0;
	targetscore=10;

}

void goal(int player_goal{

	current_x = 150;
	current_y = 110;
	last_x = 150;
	last_y = 110;
	
	dy = 10;
	dx = 10;
	
	l_paddle_x=0;
	l_paddle_y=95;
	
	r_paddle_x=310;
	r_paddle_y = 160;

	left_dy=0;
	right_dy = 0;
	if(player_goal==1){
		printf("PLAYER 1 SCORES!!!\n");
		score1=score1+1;
	}
	else if(player_goal==2){
		printf("PLAYER 2 SCORES!!!\n");
		score2=score2+1;
	}

	printf("THE SCORE IS %i - %i \n",score1,score2 );
	if(score1>=targetscore){
		printf("Player 1 win\n")
		init_game();
	}
	
	if(score2>=targetscore){
		printf("Player 2 win\n");
		init_game();
	}
	//testscreen();
}






void draw_array(uint16_t *array){
		int color;
		for(int i= 0; i<4;i++)
		{
			for(int j=0; j< 16; j++)
			{	
				if(array[i+j*4]==BLACK)
				{
					color= BLACK;
				}
				else if(array[i+j*4]==WHITE)
				{
					color= WHITE;
				}
				framebuffer[(150+80*WIDTH)+i+j*4]=color;
			}

		}




}


uint16_t nr1 [] = {
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







