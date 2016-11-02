#pragma once
#include <stdint.h>
#include <linux/fb.h>
#define WIDTH 320
#define HEIGTH 240
int fd;

//uint16_t **framebuffer[WIDTH][HEIGTH];
uint16_t *framebuffer;
struct fb_copyarea rect; //fra kompendiet, for å mappe framebufferen til minne, se init

void frameinit(void);
void openfile(void);
void closefile(int fd);
void writepixel(uint16_t pixel);
void colorpixel(uint16_t pixel);
void drawrectangle(int width,int height,char color);
