#include "frame.h"
#include "font.h"
//#include "efm32gg.h"
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

	print_col=0;
	print_row=0;

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
	
	if(current_y>=r_paddle_y && current_y<=r_paddle_y+PADDLEHEIGTH_R){
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
			set_cursor(88,96);
			print_string("Player 1 scores! \n");
			set_cursor(88,112);
			print_string("Score 1 = ");
			print_int(score1);
			print_string(",Score2 = ");
			print_int(score2);
			print_string("\n");
			refresh_screen();
			usleep(2500000);
			clear_screen();
			goal();
		}
	
	}	
	
	
	if(current_y+BALLSIZE>=l_paddle_y && current_y<=l_paddle_y+PADDLEHEIGTH_L){
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
			set_cursor(88,96);
			print_string("Player 2 scores! \n");
			set_cursor(88,112);
			print_string("Score 1 = ");
			print_int(score1);
			print_string(",Score2 = ");
			print_int(score2);
			print_string("\n");
			refresh_screen();
			usleep(2500000);
			clear_screen();
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
	
	if(l_paddle_y > BUTTOM-PADDLEHEIGTH_L){
		l_paddle_y=BUTTOM-PADDLEHEIGTH_L;
	}
	else if(l_paddle_y <TOP){
		l_paddle_y=TOP;
	}
	// Define boundries for paddle top and buttom etc
	r_paddle_y = r_paddle_y + right_dy;
	
	if(r_paddle_y > BUTTOM-PADDLEHEIGTH_R){
		r_paddle_y=BUTTOM-PADDLEHEIGTH_R;
	}
	else if(r_paddle_y <TOP){
		r_paddle_y=TOP;
	}


	// Update ball pos @ display
	drawrectangle(last_x-dx, last_y-dy, BALLSIZE, BALLSIZE, BLACK);
	drawrectangle(current_x, current_y, BALLSIZE, BALLSIZE, WHITE);
	
	// Update left paddle pos @ display
	if(left_dy==PADDLEDOWN){
		drawrectangle(l_paddle_x, l_paddle_y, PADDLEWIDTH, PADDLEHEIGTH_L, GAME_COLOR);
		drawrectangle(l_paddle_x, l_paddle_y-left_dy, PADDLEWIDTH, left_dy, BLACK);
	}
	else if(left_dy==PADDLEUP){
		drawrectangle(l_paddle_x, l_paddle_y, PADDLEWIDTH, PADDLEHEIGTH_L, GAME_COLOR);
		drawrectangle(l_paddle_x, l_paddle_y+PADDLEHEIGTH_L+PADDLEDOWN, PADDLEWIDTH, PADDLEDOWN, BLACK);
	}
	else{
		drawrectangle(l_paddle_x, l_paddle_y, PADDLEWIDTH, PADDLEHEIGTH_L, GAME_COLOR);
	}

	
		
	
	// Update rigth paddle pos @ display
	if(right_dy==PADDLEDOWN){
		drawrectangle(r_paddle_x, r_paddle_y, PADDLEWIDTH, PADDLEHEIGTH_R, GAME_COLOR);
		drawrectangle(r_paddle_x, r_paddle_y-right_dy, PADDLEWIDTH, right_dy, BLACK);
	}
	
	else if(right_dy==PADDLEUP){
		drawrectangle(r_paddle_x, r_paddle_y, PADDLEWIDTH, PADDLEHEIGTH_R, GAME_COLOR);
		drawrectangle(r_paddle_x, r_paddle_y+PADDLEHEIGTH_R+PADDLEDOWN, PADDLEWIDTH, PADDLEDOWN, BLACK);
	}
	else{
		drawrectangle(r_paddle_x, r_paddle_y, PADDLEWIDTH, PADDLEHEIGTH_R, GAME_COLOR);
	}

	refresh_screen();	
	compute_game();
}



void init_game(void){
	frameinit();
	clear_screen();
	current_x = 150;
	current_y = 110;
	last_x = 150;
	last_y = 110;
	PADDLEHEIGTH_L = 80;
	PADDLEHEIGTH_R = 80;
	GAME_COLOR = WHITE;
	

	dy=10;
	dx=20;
	
	l_paddle_x=0;
	l_paddle_y=95;
	
	r_paddle_x=310;
	r_paddle_y = 95;

	left_dy=0;
	right_dy = 0;
	
	score1=0;
	score2=0;
	targetscore=10;
	level=1;
	gameon=0;
	//drawrectangle(r_paddle_x, r_paddle_y, PADDLEWIDTH, PADDLEHEIGTH, WHITE);
	//drawrectangle(l_paddle_x, l_paddle_y, PADDLEWIDTH, PADDLEHEIGTH, WHITE);

}

void goal(void){
	current_x = 150;
	current_y = 110;
	last_x = 150;
	last_y = 110;
	
	
	l_paddle_x=0;
	l_paddle_y=95;
	
	r_paddle_x=310;
	r_paddle_y = 95;

	left_dy=0;
	right_dy = 0;
	
	if(score1>=targetscore){
		printf("Player 1 win\n");
		score1=0;
		score2=0;
		gameon=0;
		set_cursor(88,96);
		print_string("Player 1 WIN! \n");
		refresh_screen();
		usleep(2500000);
		clear_screen();
		menu();
	}
	
	if(score2>=targetscore){
		printf("Player 2 win\n");
		score1=0;
		score2=0;
		gameon=0;
		set_cursor(88,96);
		print_string("Player 2 WIN! \n");
		refresh_screen();
		usleep(2500000);
		clear_screen();
		menu();
	}
	clear_screen();
}


void print_char(int col, int row, char c){	
	int c2=c-32;
	for (int i=0; i<8; i++){
		for (int j=0; j<8; j++){
			if(((font[c2][i] >> j) & 1) == 0){
				framebuffer[col+i+j*WIDTH+(row*WIDTH)]=0;
			}
			else{
				framebuffer[col+i+j*WIDTH+(row*WIDTH)]=0xFFFF;
			}
		}
	}
}

void print_string(char *str){
	int i = 0;
	while(str[i] != '\0'){
		if(str[i]=='\n'){
			print_col=0;
			print_row=print_row+8;
		}
		else{
			print_char(print_col, print_row, str[i]);
			print_col=print_col+8;
		}
		
		

		if(print_col>WIDTH-8){
			print_row=print_row+8;
			print_col=0;
		}
		//if(print_row>HEIGTH)
		i++;
	}
	//refresh_screen();
}

void set_cursor(int col, int row){
	print_row=row;
	print_col=col;
}

void clear_screen(void){
	for(int i=0;i<WIDTH*HEIGTH;i++)
	{
		framebuffer[i]= 0;
	}
	set_cursor(0,0);
	refresh_screen();
}

void clear_line(int line){
	set_cursor(0,line*8);
	for(int i=0; i<WIDTH*8; i++){
		framebuffer[line*8*WIDTH+i]=0;
	}
	refresh_screen();
}

void print_int(int a){
	char buffer[50];
	sprintf(buffer,"%d",a);
	print_string(buffer);
}

void invert_line(int line){
	set_cursor(0,line*8);
	for(int i=0; i<WIDTH*8; i++){
		if(framebuffer[line*8*WIDTH+i]==0){
			framebuffer[line*8*WIDTH+i]=0xFFFF;
		}
		else{
			framebuffer[line*8*WIDTH+i]=0;
		}
		
	}
	//refresh_screen();
}



void settings(void){
	set_cursor(0,104);
	print_string("              Settings menu \n \n");
	print_string("              Cheat mode \n");
	print_string("              Difficult level \n");
	print_string("              Change color \n");
	invert_line(15);
	refresh_screen();

	int teller=1;
	int button;
	while(1){
		button = ((int)getc(driver));
		if(button==191){
			clear_screen();
			break;
		}
		else if(button==247){
			invert_line(teller+14);
			teller++;
			if(teller>3){
				teller=3;
			}
			invert_line(teller+14);
			refresh_screen();
		}
		else if(button==253){
			invert_line(teller+14);
			teller--;
			if(teller==0){
				teller=1;
			}
			invert_line(teller+14);
			refresh_screen();
		}
		else if(button==127){
			break;
		}
		usleep(30000);
	}

	if(button==191){
		menu();
	}
	if(teller==1){
		cheat_mode();
	}
	else if(teller==2){
		diff_level();
	}
	else if(teller==3){
		change_color();
	}

}

void menu(void){
	clear_screen();
	system("clear");
	set_cursor(0,104);
	print_string("              Main menu \n \n");
	print_string("              Start new game \n");
	print_string("              Continue game \n");
	print_string("              Settings \n");
	print_string("              Sleep mode \n");
	invert_line(15);

	int teller=1;

	refresh_screen();
	while(1){
		int button = ((int)getc(driver));
		if(button==247){
			invert_line(teller+14);
			teller++;
			if(teller>4){
				teller=4;
			}
			invert_line(teller+14);
			refresh_screen();
		}
		else if(button==253){
			invert_line(teller+14);
			teller--;
			if(teller==0){
				teller=1;
			}
			invert_line(teller+14);
			refresh_screen();
		}
		else if(button==127){
			break;
		}
		
		usleep(30000);
	}
	if(teller==1){
		init_game();
	}
	if(teller==2){
		if(gameon==0){
			clear_screen();
			print_string("No game started, starting new game \n");
			refresh_screen();
			usleep(2000000);
			init_game();
		}
	}
	
	if(teller==3){
		clear_screen();
		settings();
	}
	else if(teller==4){
		sleep_mode();
	}
	
}


void cheat_mode(void){
	PADDLEHEIGTH_R = 200;
	PADDLEHEIGTH_L = 40;
	dy=10;
	dx=20;
	clear_screen();
}

void diff_level(void){
	clear_screen();
	dy=5;
	dx=10;
}

void change_color(void){
	clear_screen();
	GAME_COLOR = RED;
}

void sleep_mode(void){

	*SCR=6;
	//__asm("WFI");
}