//interrupts.h

#ifndef __INTERRUPS_H__
#define __INTERRUPS_H__

#include <idtLoader.h>

//Todos prototipos assembler

void _irq00Handler(void);
void _irq01Handler(void);
void _irq02Handler(void);
void _irq03Handler(void);
void _irq04Handler(void);
void _irq05Handler(void);

void _syscallHandler(void);

void _exception0Handler(void);
void _exception6Handler(void);

void _cli(void);

void _sti(void);

void _hlt(void);

void picMasterMask(uint8_t mask);

void picSlaveMask(uint8_t mask);

//Termina la ejecución de la cpu.
void haltcpu(void);

uint8_t sysRTC(uint64_t timeId);

#endif /* INTERRUPS_H_ */