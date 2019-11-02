#ifndef _STD_LIB_
#define _STD_LIB_

char getChar();
void putChar(char c);
void putCharf(char c, unsigned char format);
void print(char * string);
void printf(char * string, unsigned char format);
void println(char * string);
void scanf(char * output, int n);
void setCursorPos(int row, int col);
#endif