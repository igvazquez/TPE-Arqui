#ifndef SCREEN_DRV_
#define SCREEN_DRV_

#include <stdint.h>
#include <videoDriver.h>

#define DEFAULT_BACKGROUND_COLOR 0x000000 //Negro
#define DEFAULT_TEXT_COLOR 0xFFFFFF //Blanco

void ncNewline();
void ncPrintDec(uint64_t value);
void ncPrintHex(uint64_t value);
void ncPrintBin(uint64_t value);
void ncPrintBase(uint64_t value, uint32_t base);
void ncClear();

void printString(char* word);

void printChar(char c);

void setColorMode(unsigned int newBackgroundColor, unsigned int newFontColor);

void setCursorPos(unsigned int x, unsigned int y);

//void moveCursorPos(int row, int col);

void printFormatedChar(char c, unsigned int newBackgroundColor, unsigned int newFontColor);

void printFormatedString(char* word, unsigned int newBackgroundColor, unsigned int newFontColor);

#endif