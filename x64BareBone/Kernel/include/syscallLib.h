#ifndef _SYSCALLIB_H_
#define _SYSCALLIB_H_

#include <defs.h>
#include <stdint.h>
#include <videoDriver.h>

char sysGetChar();
void sysWriteToScreen( char * string, uint8_t row, uint8_t col);

#endif