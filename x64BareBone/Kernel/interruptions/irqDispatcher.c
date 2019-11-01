#include <time.h>
#include <stdint.h>
#include <keyboardDriver.h>

static void int_20();
static void int_21();

static void (*intFunctionArray[])() = {int_20, int_21};

void irqDispatcher(uint64_t irq) {
	intFunctionArray[irq]();
}

void int_20() {
	timer_handler();
}


void int_21(){
	storeKey();
}
