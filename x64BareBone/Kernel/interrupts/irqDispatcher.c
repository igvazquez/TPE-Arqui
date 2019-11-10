//irqDispathcer.c

#include <keyboardDriver.h>
#include <timerTick.h>
#include <stdint.h>

//ASM
static void int_20();
static void int_21();

static void (*intFunctionArray[])() = {int_20, int_21};

void irqDispatcher(uint64_t irq) {
	intFunctionArray[irq]();
}

static void int_20() {
	timer_handler();
}

static void int_21(){
	storeKey();
}