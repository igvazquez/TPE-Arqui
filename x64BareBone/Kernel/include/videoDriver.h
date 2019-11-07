#ifndef VIDEO_DRV_H
#define VIDEO_DRV_H

#include <stdint.h>
#include <font.h>

void init_VM_Driver();

void drawPixel(unsigned int x, unsigned int y, int color);

void copyPixel(unsigned int xSource, unsigned int ySource, unsigned int xDest, unsigned int yDest);

void drawChar(int x, int y, char character, int fontColor, int backgroundColor);

int getScreenWidth();

int getScreenHeight();

#endif