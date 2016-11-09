#pragma once
#include <stdint.h>
#include <linux/fb.h>
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
#define PADDLEHEIGTH 80
#define PADDLEWIDTH 10
#define PADDLEUP -10
#define PADDLEDOWN	10
void refresh_screen(void);

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