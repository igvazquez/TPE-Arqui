#include <stdLib.h>

static char buffer[64] = { '0' };

char getCharAsm();
void write(char* string, unsigned int backgroundColor, unsigned int fontColor);
void setCursorPosAsm(unsigned int row, unsigned int col);
static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);
int getTicksElapsedAsm();
uint64_t getRegister(int register);

void ncPrintBin(uint64_t value){
	ncPrintBase(value, 2);
}

void ncPrintBase(uint64_t value, uint32_t base){
    uintToBase(value, buffer, base);
    print(buffer);
}
static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base){
	char *p = buffer;
	char *p1, *p2;
	uint32_t digits = 0;

	//Calculate characters for each digit
	do
	{
		uint32_t remainder = value % base;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	}
	while (value /= base);

	// Terminate string in buffer.
	*p = 0;

	//Reverse string in buffer.
	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2)
	{
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
}
void putChar(char c){
    char string[2] = {c, 0};
    write(string, DEFAULT_BACKGROUND_COLOR, DEFAULT_FONT_COLOR);
}
char getChar(){
    return getCharAsm();
}
void setCursorPos(int row, int col){
    setCursorPosAsm(row, col);
}
void scanf(char * output, int n){
    char c;
    int counter=0;
    while(counter < n-1 && (c=getChar())!='\n'){
        if(c){

            if(c == '\b'){
                if(counter >= 1)
                    counter--;

            }else if(c == '\t')
                output[counter++]=' ';

            else
                output[counter++]=c;
        }
    }
    output[counter]=0;   
}
void putCharf(char c, unsigned int backgroundColor, unsigned int fontColor){
    char string[2] = {c, 0};
    write(string,backgroundColor, fontColor);
}
void printf(char * string, unsigned int backgroundColor, unsigned int fontColor){
    write(string, backgroundColor, fontColor);
}
void println(char * string){
    write(string, DEFAULT_BACKGROUND_COLOR, DEFAULT_FONT_COLOR);
    putChar('\n');
}

void print(char * string){
    write(string, DEFAULT_BACKGROUND_COLOR, DEFAULT_FONT_COLOR);
}

int strlen(char * s){
    int rta = 0;
    while(*s){
        rta++;
        s++;
    }
    return rta;
}

int getTicksElapsed(){
    return getTicksElapsedAsm();
}

int strcmp(char * s1, char * s2){
    while(*s1 != 0 && *s2 != 0){

        if(*s1 == *s2){
            s1++;
            s2++;
        } else 
            return *s1 - *s2;
    }

    if(*s1 == 0 && *s2 == 0)
        return 0;

    else if(*s2 == 0)
        return 1;

    else 
        return -1;

}
void printRegisters(){
		print("Registro RAX: ");
		ncPrintBin(getRegister(RAX));
		putChar('\n');

		print("Registro RBX: ");
		ncPrintBin(getRegister(RBX));
		putChar('\n');

		print("Registro RCX: ");
		ncPrintBin(getRegister(RCX));
		putChar('\n');

		print("Registro RDX: ");
		ncPrintBin(getRegister(RDX));
		putChar('\n');

		print("Registro RBP: ");
		ncPrintBin(getRegister(RBP));
		putChar('\n');

		print("Registro RDI: ");
		ncPrintBin(getRegister(RDI));
		putChar('\n');

		print("Registro RSI: ");
		ncPrintBin(getRegister(RSI));
		putChar('\n');

		print("Registro R8: ");
		ncPrintBin(getRegister(R8));
		putChar('\n');

		print("Registro R9: ");
		ncPrintBin(getRegister(R9));
		putChar('\n');

		print("Registro R10: ");
		ncPrintBin(getRegister(R10));
		putChar('\n');

		print("Registro R11: ");
		ncPrintBin(getRegister(R11));
		putChar('\n');

		print("Registro R12: ");
		ncPrintBin(getRegister(R12));
		putChar('\n');

		print("Registro R13: ");
		ncPrintBin(getRegister(R13));
		putChar('\n');

		print("Registro R14: ");
		ncPrintBin(getRegister(R14));
		putChar('\n');

		print("Registro R15: ");
		ncPrintBin(getRegister(R15));
		putChar('\n');

		// printString("Registro RPI: ");
		// ncPrintBin(getRegister(RIP));
		// printChar('\n');
}