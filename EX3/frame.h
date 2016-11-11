#define _BSD_SOURCE
#pragma once
#include <stdint.h>
#include <linux/fb.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>





#define SCR          ((volatile uint32_t*)0xe000ed10)
#define WIDTH 320
#define HEIGTH 240
int fd;
#define BLUE 0b0000000000011111
#define GREEN 0b000001111100000
#define RED  0b1111100000000000
#define WHITE 0b1111111111111111
#define BLACK 0b0000000000000000

#define TOP 0
#define BUTTOM 240
#define LEFT 0
#define RIGTH 320

#define BALLSIZE 10
//#define PADDLEHEIGTH 80
int PADDLEHEIGTH_L;
int PADDLEHEIGTH_R;
int GAME_COLOR;


#define PADDLEWIDTH 10
#define PADDLEUP -10
#define PADDLEDOWN	10
void refresh_screen(void);
void print_char(int col, int row, char c);
void print_string(char *str);
void set_cursor(int col, int row);
void clear_line(int line);
void clear_screen(void);
void print_int(int a);
void invert_line(int line);
void menu(void);
void settings(void);
void sleep_mode(void);


void cheat_mode(void);
void diff_level(void);
void change_color(void);


FILE *driver;
int print_col;
int print_row;

	int current_x;
	int current_y;
	int last_x;
	int last_y;
	
	int dy;
	int dx;
	
	int l_paddle_x;
	int l_paddle_y;
	
	int r_paddle_x;
	int r_paddle_y;

	int left_dy;
	int right_dy;

	int score1;
	int score2;
	int targetscore;
	int level;
	int gameon;

uint16_t *framebuffer;
struct fb_copyarea rect; //fra kompendiet, for å mappe framebufferen til minne, se init

void frameinit(void);
void closefile(void);
/*void writepixel(uint16_t pixel);
void colorpixel(uint16_t pixel);*/
void drawrectangle(int column, int row,int rec_width,int rec_heigth, int color);
void testscreen(void);

void initDisplay();
void fill_screen(uint16_t value);

void refresh_screen();
void goal(void);

void updategame(int button);
void compute_game(void);

void init_game(void);
void draw_array(uint16_t *array);


void drawchar(char c);
void draw_text(char *matrix);
void draw_text2(char *matrix);
void draw_rect(int x, int y, int color);