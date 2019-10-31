#ifndef VIDEO_DRV_H
#define VIDEO_DRV_H

#include <stdint.h>

// Defines referentes a FIRST_VIDEO_BYTE
#define DEFAULT_COLOR_MODE 0x07
#define VIDEO_HOR_LEN 80
#define VIDEO_VER_LEN 25
#define FIRST_VIDEO_BYTE (char*)0xB8000
#define LAST_VIDEO_BYTE (char*)(FIRST_VIDEO_BYTE + VIDEO_HOR_LEN * VIDEO_VER_LEN * 2 - 1)
#define ERROR_COLOR_MODE 0x4

#define IS_IN_BOUNDS(x) ((x) >= FIRST_VIDEO_BYTE && (x) <= LAST_VIDEO_BYTE)

void ncNewline();
void ncPrintDec(uint64_t value);
void ncPrintHex(uint64_t value);
void ncPrintBin(uint64_t value);
void ncPrintBase(uint64_t value, uint32_t base);
void ncClear();

void printString(char* word);

void printn(char* word, unsigned int lenght);

void printChar(char c);

void setColorMode(unsigned char colorMode);

void setCursorPos(unsigned int row, unsigned int col);

void moveCursorPos(int row, int col);

#endif