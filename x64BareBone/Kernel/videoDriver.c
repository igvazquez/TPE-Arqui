#include <videoDriver.h>

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);

static char buffer[64] = { '0' };

char * v = FIRST_VIDEO_BYTE;

unsigned char colorMode = DEFAULT_COLOR_MODE;

static void scrollDownOnce();
static int getCursorCol();
static int getCursorRow();
static void backspace();
static void enter();
static void tab();
static int parseSpecialChars(char c);

void ncNewline(){
	do
	{
		printChar(' ');
	}
	while((uint64_t)(v - FIRST_VIDEO_BYTE) % (VIDEO_HOR_LEN * 2) != 0);
}

void ncPrintDec(uint64_t value){
	ncPrintBase(value, 10);
}

void ncPrintHex(uint64_t value){
	ncPrintBase(value, 16);
}

void ncPrintBin(uint64_t value){
	ncPrintBase(value, 2);
}

void ncPrintBase(uint64_t value, uint32_t base){
    uintToBase(value, buffer, base);
    printString(buffer);
}

void ncClear(){
	int i;

	for (i = 0; i < VIDEO_VER_LEN * VIDEO_HOR_LEN; i++)
		v[i * 2] = ' ';
	v = FIRST_VIDEO_BYTE;
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

void printString(char* word){
	char * s = word;

	while(*s != 0)
		printChar(*s++);
}

void printFormatedString(char* word, unsigned char newColorMode){
	unsigned char colorModeBackup = colorMode;
	setColorMode(newColorMode);
	printString(word);
	setColorMode(colorModeBackup);
}

void printFormatedChar(char c, unsigned char newColorMode){
	unsigned char colorModeBackup = colorMode;
	setColorMode(newColorMode);
	printChar(c);
	setColorMode(colorModeBackup);
}

void printChar(char c){
	if(parseSpecialChars(c))
		return;

	*v = c;
	*(v + 1) = colorMode;
	v += 2;
	if(v > LAST_VIDEO_BYTE){
		scrollDownOnce();
		setCursorPos(VIDEO_VER_LEN - 1, 0);
	}
}

void setColorMode(unsigned char newColorMode){
    colorMode = newColorMode;
}

//Absolute movement
void setCursorPos(unsigned int row, unsigned int col){
    if(row < VIDEO_VER_LEN && col < VIDEO_HOR_LEN){
        v = FIRST_VIDEO_BYTE + VIDEO_HOR_LEN * 2 * row + col * 2;
    }
}

//Relative movement
void moveCursorPos(int row, int col){
    char * aux = v + 2 * VIDEO_HOR_LEN * row + col * 2;
    if(IS_IN_BOUNDS(aux)){
        v = aux;
    }
}

static int getCursorRow(){
	return (v - FIRST_VIDEO_BYTE) / 2 / VIDEO_HOR_LEN;
}

static int getCursorCol(){
	return (v - FIRST_VIDEO_BYTE) / 2 % VIDEO_HOR_LEN;
}

static void scrollDownOnce(){
	char* aux;
	for (aux = FIRST_VIDEO_BYTE; aux + VIDEO_HOR_LEN * 2 <= LAST_VIDEO_BYTE; aux++)
		*aux = *(aux + VIDEO_HOR_LEN * 2);
	
	for (; aux <= LAST_VIDEO_BYTE; aux+=2){
		*aux = ' ';
		*(aux + 1) = colorMode;
	}
}

static void tab(){
	int currentCol = getCursorCol();
	if(currentCol + 4 >= VIDEO_HOR_LEN){
		enter();
        moveCursorPos(0, currentCol + 4 - VIDEO_HOR_LEN);
	} else 
		moveCursorPos(0, 4);
}

static void enter(){
	int currentRow = getCursorRow();
	if(currentRow + 1 >= VIDEO_VER_LEN){
		scrollDownOnce();
		setCursorPos(VIDEO_VER_LEN - 1, 0);
	} else
		setCursorPos(currentRow + 1, 0);
}

static void backspace(){
	moveCursorPos(0,-1);
    printChar(' ');
    moveCursorPos(0,-1);
}

static int parseSpecialChars(char c){
	switch (c){
		case '\n':
			enter();
			break;

		case '\t':
			tab();
			break;

		case '\b':
			backspace();
			break;
		
		default:
			return 0;
			break;
	}
	return 1;
}