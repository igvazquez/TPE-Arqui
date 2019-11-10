//videoDriver.h
#ifndef __VIDEO_DRIVER_H__
#define __VIDEO_DRIVER_H__

#include <stdint.h>
#include <font.h>

void init_VM_Driver();

void drawPixel(unsigned int x, unsigned int y, int color);

void drawChar(int x, int y, char character, int fontColor, int backgroundColor);

void copyPixel(unsigned int xSource, unsigned int ySource, unsigned int xDest, unsigned int yDest);

int getVerticalPixelCount();

int getHorizontalPixelCount();

#endif