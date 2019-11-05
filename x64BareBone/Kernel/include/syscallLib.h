#ifndef _SYSCALLIB_H_
#define _SYSCALLIB_H_

#include <defs.h>
#include <stdint.h>
#include <videoDriver.h>

char sysGetChar();
void sysSetCursor(uint8_t row, uint8_t col);
void sysWrite(char *string, unsigned char format);
void printRegisters();
uint64_t getRegister(int register);
#endif