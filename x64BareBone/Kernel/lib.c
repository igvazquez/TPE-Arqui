//lib.c
#include <lib.h>

void * memset(void * destination, int32_t c, uint64_t length){
	uint8_t chr = (uint8_t)c;
	char * dst = (char*)destination;

	while(length--)
		dst[length] = chr;

	return destination;
}

void * memcpy(void * destination, const void * source, uint64_t length){
	/*
	* memcpy does not support overlapping buffers, so always do it
	* forwards. (Don't change this without adjusting memmove.)
	*
	* For speedy copying, optimize the common case where both pointers
	* and the length are word-aligned, and copy word-at-a-time instead
	* of byte-at-a-time. Otherwise, copy by bytes.
	*
	* The alignment logic below should be portable. We rely on
	* the compiler to be reasonably intelligent about optimizing
	* the divides and modulos out. Fortunately, it is.
	*/
	uint64_t i;

	if ((uint64_t)destination % sizeof(uint32_t) == 0 &&
		(uint64_t)source % sizeof(uint32_t) == 0 &&
		length % sizeof(uint32_t) == 0)
	{
		uint32_t *d = (uint32_t *) destination;
		const uint32_t *s = (const uint32_t *)source;

		for (i = 0; i < length / sizeof(uint32_t); i++)
			d[i] = s[i];
	}
	else
	{
		uint8_t * d = (uint8_t*)destination;
		const uint8_t * s = (const uint8_t*)source;

		for (i = 0; i < length; i++)
			d[i] = s[i];
	}

	return destination;
}

void printRegisters(){
	
		printString("Registro RAX: ");
		ncPrintBin(getRegister(RAX));
		printChar('\n');

		printString("Registro RBX: ");
		ncPrintBin(getRegister(RBX));
		printChar('\n');

		printString("Registro RCX: ");
		ncPrintBin(getRegister(RCX));
		printChar('\n');

		printString("Registro RDX: ");
		ncPrintBin(getRegister(RDX));
		printChar('\n');

		printString("Registro RBP: ");
		ncPrintBin(getRegister(RBP));
		printChar('\n');

		printString("Registro RDI: ");
		ncPrintBin(getRegister(RDI));
		printChar('\n');

		printString("Registro RSI: ");
		ncPrintBin(getRegister(RSI));
		printChar('\n');

		printString("Registro R8: ");
		ncPrintBin(getRegister(R8));
		printChar('\n');

		printString("Registro R9: ");
		ncPrintBin(getRegister(R9));
		printChar('\n');

		printString("Registro R10: ");
		ncPrintBin(getRegister(R10));
		printChar('\n');

		printString("Registro R11: ");
		ncPrintBin(getRegister(R11));
		printChar('\n');

		printString("Registro R12: ");
		ncPrintBin(getRegister(R12));
		printChar('\n');

		printString("Registro R13: ");
		ncPrintBin(getRegister(R13));
		printChar('\n');

		printString("Registro R14: ");
		ncPrintBin(getRegister(R14));
		printChar('\n');

		printString("Registro R15: ");
		ncPrintBin(getRegister(R15));
		printChar('\n');

		// printString("Registro RPI: ");
		// ncPrintBin(getRegister(RIP));
		// printChar('\n');
}