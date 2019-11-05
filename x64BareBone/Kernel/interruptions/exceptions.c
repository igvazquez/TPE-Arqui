#include <videoDriver.h>

#define ZERO_EXCEPTION_ID 0
#define INVALID_UPCODE_ID 6

static void zero_division();
static void invalid_upcode();

void exceptionDispatcher(int exception) {
	switch(exception){
		case ZERO_EXCEPTION_ID:
			zero_division();
			break;
		case INVALID_UPCODE_ID:
			invalid_upcode();
			break;
	}
}

static void zero_division() {
	printString("ERROR 0: DIVISION POR 0\n");
	printRegisters();
	while(1);
}
static void invalid_upcode(){
	printString("ERROR 6: CODIGO DE OPERACION INVALIDO\n");
	printRegisters();
	while(1);
}