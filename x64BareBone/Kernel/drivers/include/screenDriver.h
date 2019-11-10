//screenDriver.h

#ifndef __SCREEN_DRV_H__
#define __SCREEN_DRV_H__

#include <stdint.h>
#include <videoDriver.h>

#define DEFAULT_BACKGROUND_COLOR 0x000000 //Negro
#define DEFAULT_FONT_COLOR 0xFFFFFF //Blanco

void initializeScreenDriver();

void printChar(char c);
void printFormatedChar(char c, unsigned int newBackgroundColor, unsigned int newFontColor);

void printString(char* word);
void printFormatedString(char* word, unsigned int newBackgroundColor, unsigned int newFontColor);

//Setters
void setCursorPos( int row,  int col);
void setColorMode(unsigned int newBackgroundColor, unsigned int newFontColor);

//Auxiliar functions
void newLine();
void clearScreen();

//Print Numbers
void ncPrintDec(uint64_t value);
void ncPrintHex(uint64_t value);
void ncPrintBin(uint64_t value);
void ncPrintBase(uint64_t value, uint32_t base);

#endif