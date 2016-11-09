#include "frame.h"
#include "font.h"
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


void compute_game(void){
	
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
			printf("Player 1 scores!\n");
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
			printf("Player 2 scores!\n");
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

void updategame(int button){
	
	
	// Button handle, set dx, dy osv /////////
	if(button == 255){
		left_dy=0;
		right_dy=0;
	}

	if((button >> 1 & 1)==0){
		left_dy=PADDLEUP;
		//printf("Left up \n");
	}
	else if((button >> 3 & 1)==0){
		left_dy=PADDLEDOWN;
		//printf("Left down \n");
	}

	if((button >> 5 & 1)==0){
		right_dy=PADDLEUP;
		//printf("Right up \n");
	}
	else if((button >> 7 & 1)==0){
		right_dy=PADDLEDOWN;
		//printf("Right down \n");
	}


	last_x = current_x + dx;
	current_x = current_x + dx;
	
	last_y = current_y + dy;
	current_y = current_y + dy;
	
	l_paddle_y = l_paddle_y + left_dy;
	
	if(l_paddle_y > BUTTOM-PADDLEHEIGTH){
		l_paddle_y=BUTTOM-PADDLEHEIGTH;
	}
	else if(l_paddle_y <TOP){
		l_paddle_y=TOP;
	}
	// Define boundries for paddle top and buttom etc
	r_paddle_y = r_paddle_y + right_dy;
	
	if(r_paddle_y > BUTTOM-PADDLEHEIGTH){
		r_paddle_y=BUTTOM-PADDLEHEIGTH;
	}
	else if(r_paddle_y <TOP){
		r_paddle_y=TOP;
	}


	// Update ball pos @ display
	drawrectangle(last_x-dx, last_y-dy, BALLSIZE, BALLSIZE, BLACK);
	drawrectangle(current_x, current_y, BALLSIZE, BALLSIZE, WHITE);
	
	// Update left paddle pos @ display
	if(left_dy==PADDLEDOWN){
		drawrectangle(l_paddle_x, l_paddle_y, PADDLEWIDTH, PADDLEHEIGTH, WHITE);
		drawrectangle(l_paddle_x, l_paddle_y-left_dy, PADDLEWIDTH, left_dy, BLACK);
	}
	else if(left_dy==PADDLEUP){
		drawrectangle(l_paddle_x, l_paddle_y, PADDLEWIDTH, PADDLEHEIGTH, WHITE);
		drawrectangle(l_paddle_x, l_paddle_y+PADDLEHEIGTH+PADDLEDOWN, PADDLEWIDTH, PADDLEDOWN, BLACK);
	}
	else{
		drawrectangle(l_paddle_x, l_paddle_y, PADDLEWIDTH, PADDLEHEIGTH, WHITE);
	}

	
		
	
	// Update rigth paddle pos @ display
	if(right_dy==PADDLEDOWN){
		drawrectangle(r_paddle_x, r_paddle_y, PADDLEWIDTH, PADDLEHEIGTH, WHITE);
		drawrectangle(r_paddle_x, r_paddle_y-right_dy, PADDLEWIDTH, right_dy, BLACK);
	}
	
	else if(right_dy==PADDLEUP){
		drawrectangle(r_paddle_x, r_paddle_y, PADDLEWIDTH, PADDLEHEIGTH, WHITE);
		drawrectangle(r_paddle_x, r_paddle_y+PADDLEHEIGTH+PADDLEDOWN, PADDLEWIDTH, PADDLEDOWN, BLACK);
	}
	else{
		drawrectangle(r_paddle_x, r_paddle_y, PADDLEWIDTH, PADDLEHEIGTH, WHITE);
	}

	refresh_screen();	
	compute_game();
}



void init_game(void){
	frameinit();
	testscreen();
	current_x = 150;
	current_y = 110;
	last_x = 150;
	last_y = 110;
	
	dy = 0;
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

	//drawrectangle(r_paddle_x, r_paddle_y, PADDLEWIDTH, PADDLEHEIGTH, WHITE);
	//drawrectangle(l_paddle_x, l_paddle_y, PADDLEWIDTH, PADDLEHEIGTH, WHITE);

}

void goal(void){
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
	
	if(score1>=targetscore){
		printf("Player 1 win\n");
		init_game();
	}
	
	if(score2>=targetscore){
		printf("Player 2 win\n");
		init_game();
	}
	testscreen();
}

void draw_array(uint16_t *array){
		int color;
		for(int i= 0; i<16;i++)
		{
			for(int j=0; j< 4; j++)
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

		refresh_screen();
}




void drawchar(char c){
	int j = c;
	j=c-32;
	for(uint16_t i = 0; i<12; i++){
		framebuffer[chars_8x8_bits[j+i]] = WHITE;
	}
	refresh_screen();
}

void draw_text(char *matrix){
	int color = 34;
	for(int i = 0; i < 32; i++){
		for(int j = 0; j < 24; j++){
			switch(matrix[i + j * 32]){
				case 'X':
				color =0x0000;
				break;
				case 'Y':
				color = 0xFF00;
				break;
				case 'G':
				color = 0x008F;
				break;
				case 'B':
				color = 0x00FF;
				break;
				case 'R':
				color = 0xF000;
				break;
				case 'W':
				color = 0xFFFF;
				default:
				break; 
			}	

			drawrectangle(i, j, 10, 10, color);
		}
	}
	refresh_screen();
}


void draw_rect(int x, int y, int color){
	for(int i = x; i < x + 10; i++){
		for(int j = y; j < y + 10; j++){
			framebuffer[i + j * WIDTH] = color;
		}
	}
}


void draw_text2(char *matrix){
	int color = 34;
	for(int i = 0; i < 32; i++){
		for(int j = 0; j < 24; j++){
			switch(matrix[i + j * 32]){
				case 'X':
				color =0x0000;
				break;
				case 'Y':
				color = 0xFF00;
				break;
				case 'G':
				color = 0x008F;
				break;
				case 'B':
				color = 0x00FF;
				break;
				case 'R':
				color = 0xF000;
				break;
				case 'W':
				color = 0xFFFF;
				default:
				break; 
			}	

			draw_rect(i*10, j*10, color);
		}
	}
	refresh_screen();
}