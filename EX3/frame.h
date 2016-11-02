#pragma once
#include <stdint.h>
#include <linux/fb.h>
#define WIDTH 320
#define HEIGTH 240
int fd;
#define BLUE 0b0000000000011111
#define GREEN 0b000001111100000
#define RED  0b1111100000000000
uint16_t *framebuffer;
struct fb_copyarea rect; //fra kompendiet, for å mappe framebufferen til minne, se init

void frameinit(void);
void closefile(void);
/*void writepixel(uint16_t pixel);
void colorpixel(uint16_t pixel);*/
void drawrectangle(int column, int row,int rec_width,int rec_heigth);
void testscreen(void);

void initDisplay();
void fill_screen(uint16_t value);

void refresh_screen();

void draw_rect(int x, int y, int color);
