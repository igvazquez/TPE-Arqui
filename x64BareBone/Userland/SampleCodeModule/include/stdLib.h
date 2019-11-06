#ifndef _STD_LIB_
#define _STD_LIB_
#include <stdint.h>
enum registers {RAX=0, RBX, RCX, RDX, RBP, RDI, RSI, R8, R9, R10, R11, R12, R13, R14, R15, RIP};

char getChar();
void ncPrintBin(uint64_t value);
void putChar(char c);
void putCharf(char c, unsigned char format);
void print(char * string);
void printf(char * string, unsigned char format);
void println(char * string);
void scanf(char * output, int n);
void setCursorPos(int row, int col);
int strlen(char * s);
int getTicksElapsed();
void getAllRegisters();
int strcmp(char * s1, char * s2);
void printRegisters();
void ncPrintBase(uint64_t value, uint32_t base);
#endif