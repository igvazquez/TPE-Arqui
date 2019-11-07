#include <screenDriver.h>

#define SCREEN_WIDTH (getScreenWidth() / CHAR_WIDTH) //Ancho matriz pantalla
#define SCREEN_HEIGHT (getScreenHeight() / CHAR_HEIGHT) //Alto matriz pantalla
#define LAST_COLOR_MODE 0xFFFFFF //Color maximo
#define IS_CURSOR_IN_BOUNDS(x, y) ((x) >= 0 && (x) < SCREEN_WIDTH && (y) >= 0 && (y) < SCREEN_HEIGHT)

unsigned int cursorPosX = 0;
unsigned int cursorPosY = 0;

unsigned int backgroundColor = DEFAULT_BACKGROUND_COLOR;
unsigned int textColor = DEFAULT_TEXT_COLOR;

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);
static void scrollDownOnce();
static void backspace();
static void enter();
static void tab();
static int parseSpecialChars(char c);

void ncNewline(){
	printChar('\n');
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
	static char buffer[64] = { '0' };
    uintToBase(value, buffer, base);
    printString(buffer);
}

void ncClear(){
	setCursorPos(0, 0);
	for (int i = 0; i < SCREEN_HEIGHT; i++){
		for (int j = 0; j < SCREEN_WIDTH; j++){
			printChar(' ');
		}	
	}
	setCursorPos(0, 0);
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

void printFormatedString(char* word, unsigned int newBackgroundColor, unsigned int newFontColor){
	unsigned int backgroundColorBackup = backgroundColor;
	unsigned int fontColorBackup = textColor;

	setColorMode(newBackgroundColor, newFontColor);
	printString(word);
	setColorMode(backgroundColorBackup, fontColorBackup);
}

void printFormatedChar(char c, unsigned int newBackgroundColor, unsigned int newFontColor){
	unsigned int backgroundColorBackup = backgroundColor;
	unsigned int fontColorBackup = textColor;

	setColorMode(newBackgroundColor, newFontColor);
	printChar(c);
	setColorMode(backgroundColorBackup, fontColorBackup);
}

void printChar(char c){
	if(parseSpecialChars(c))
		return;

	if(cursorPosY >= SCREEN_HEIGHT){
		scrollDownOnce();
		setCursorPos(0, SCREEN_HEIGHT - 1);
	}

	drawChar(cursorPosX*CHAR_WIDTH, cursorPosY*CHAR_HEIGHT, c, backgroundColor, textColor);

	if(cursorPosX + 1 >= SCREEN_WIDTH){
        cursorPosY++;
		cursorPosX = 0;
	}else
        cursorPosX++;
}

void setColorMode(unsigned int newBackgroundColor, unsigned int newFontColor){
	if(newBackgroundColor < 0 || newBackgroundColor >= LAST_COLOR_MODE || newFontColor < 0 || newFontColor >= LAST_COLOR_MODE)
		return;

    backgroundColor = newBackgroundColor;
	textColor = newFontColor;
}

//Absolute movement
void setCursorPos(unsigned int x, unsigned int y){
    if( 1/*IS_CURSOR_IN_BOUNDS(x, y)*/){
        cursorPosX = x;
		cursorPosY = y;
    }
}

//Relative movement
// void moveCursorPos(int row, int col){
//     char * aux = cursorPos + 2 * VIDEO_HOR_LEN * row + col * 2;
//     if(IS_IN_BOUNDS(aux)){
//         cursorPos = aux;
//     }
// }

static void scrollDownOnce(){
	for (int i = 0; i < getScreenHeight() - CHAR_HEIGHT; i++){
		for (int j = 0; j < getScreenWidth(); j++){
			copyPixel(j, i + CHAR_HEIGHT, j, i);
		}
	}

	unsigned int cursorPosXBackup = cursorPosX;
	unsigned int cursorPosYBackup = cursorPosY;

	cursorPosX = 0;
	cursorPosY = SCREEN_HEIGHT - 1;
	
	for (int i = 0; i < SCREEN_WIDTH; i++){
		printChar(' ');
	}

	cursorPosX = cursorPosXBackup;
	cursorPosY = cursorPosYBackup;
}

static void tab(){

	if(cursorPosX + 4 >= SCREEN_WIDTH)
		cursorPosX = SCREEN_WIDTH;
	else 
		cursorPosX += 4;
}

static void enter(){
	if(cursorPosY + 1 >= SCREEN_HEIGHT){
		scrollDownOnce();
		setCursorPos(0, SCREEN_HEIGHT - 1);
	} else
		setCursorPos(0, cursorPosY + 1);
}

static void backspace(){

	if(cursorPosX - 1 < 0){
		setCursorPos(SCREEN_WIDTH - 1, cursorPosY - 1);
		printChar(' ');
		setCursorPos(SCREEN_WIDTH - 1, cursorPosY - 1);
	}else{
		cursorPosX--;
		printChar(' ');
		cursorPosX--;
	}
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