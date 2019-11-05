#ifndef LIB_H
#define LIB_H

#include <stdint.h>
#include <videoDriver.h>

enum registers {RAX=0, RBX, RCX, RDX, RBP, RDI, RSI, R8, R9, R10, R11, R12, R13, R14, R15, RIP};

void * memset(void * destination, int32_t character, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);

char *cpuVendor(char *result);
void printRegisters();
uint64_t getRegister(int register);
void printBinary(uint64_t n);
#endif