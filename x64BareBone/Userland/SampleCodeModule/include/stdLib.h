//stdLib.h
#ifndef __STD_LIB_H__
#define __STD_LIB_H__

#include <stdint.h>

enum registers {RAX=0, RBX, RCX, RDX, RBP, RDI, RSI, R8, R9, R10, R11, R12, R13, R14, R15, RIP};

//TODO clear screen 

void putChar(char c);

void putCharf(char c, unsigned int backgroundColor, unsigned int fontColor);

void print(char * string);

void printf(char * string, unsigned int backgroundColor, unsigned int fontColor);

void println(char * string);

void scanf(char * output, int n);

int strlen(char * s);

int strcmp(char * s1, char * s2);

void ncPrintBin(uint64_t value);

void ncPrintBase(uint64_t value, uint32_t base);

int getScreenHeight();

int getScreenWidth();

int bsdToInt(uint8_t input);

void usrClearScreen();

//ASM
extern int getTicksElapsed();

extern int getVerticalPixelCount();

extern int getHorizontalPixelCount();

extern char getChar();

extern void write(char* string, unsigned int backgroundColor, unsigned int fontColor);

extern void printAllRegisters();

extern void drawPixel(unsigned int x, unsigned int y, int color);

extern void setCursorPos(int row, int col);

extern void triggerException6Asm();

extern uint64_t getRegister(enum registers reg);

#endif