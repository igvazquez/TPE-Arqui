//lib.h
#ifndef __LIB_H__
#define __LIB_H__

#include <stdint.h>
#include <screenDriver.h>

enum registers {RAX=0, RBX, RCX, RDX, RBP, RDI, RSI, R8, R9, R10, R11, R12, R13, R14, R15, RIP};

void * memset(void * destination, int32_t character, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);

void printRegisters();

extern uint64_t getRegister(int register);

extern char *cpuVendor(char *result);

#endif