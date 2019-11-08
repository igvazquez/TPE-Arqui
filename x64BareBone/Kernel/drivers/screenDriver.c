//screenDriver.c

#include <screenDriver.h>

#define LAST_COLOR_MODE 0xFFFFFF //Color maximo

//Variables
    unsigned int cursorRow, cursorCol ;

    int screenWidth, screenHeight;

    unsigned int backgroundColor = DEFAULT_BACKGROUND_COLOR;
    unsigned int fontColor = DEFAULT_FONT_COLOR;
//End Variables

//Static prototypes
    static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);
    static int inBounds(int row, int col);
    static int parseSpecialChars(char c);
    static void scrollDownOnce();
    static void backspace();
    static void enter();
    static void tab();
//End static prototypes

void initializeScreenDriver(){
    init_VM_Driver();
    screenWidth = getHorizontalPixelCount() / CHAR_WIDTH;
    screenHeight = getVerticalPixelCount() / CHAR_HEIGHT;
    clearScreen();
}

void printString(char* word){
	char * s = word;

	while(*s != 0)
		printChar(*s++);
}

void printFormatedString(char* word, unsigned int newBackgroundColor, unsigned int newFontColor){
	unsigned int backgroundColorBackup = backgroundColor;
	unsigned int fontColorBackup = fontColor;

	setColorMode(newBackgroundColor, newFontColor);
	printString(word);
	setColorMode(backgroundColorBackup, fontColorBackup);
}

void printChar(char c){
	if(parseSpecialChars(c))
		return;

	if(cursorRow >= screenHeight){
		scrollDownOnce();
		setCursorPos(screenHeight - 1, 0);
	}

	drawChar(cursorCol*CHAR_WIDTH, cursorRow*CHAR_HEIGHT, c, fontColor, backgroundColor);

	if(cursorCol + 1 >= screenWidth){
        cursorRow++;
		cursorCol = 0;
	}else
        cursorCol++;
}

void printFormatedChar(char c, unsigned int newBackgroundColor, unsigned int newFontColor){
	
    unsigned int backgroundColorBackup = backgroundColor;
	unsigned int fontColorBackup = fontColor;

	setColorMode(newBackgroundColor, newFontColor);
	printChar(c);
	setColorMode(backgroundColorBackup, fontColorBackup);
}

//Setters
    void setColorMode(unsigned int newBackgroundColor, unsigned int newFontColor){
        
        if(newBackgroundColor < 0 || newBackgroundColor > LAST_COLOR_MODE || newFontColor < 0 || newFontColor > LAST_COLOR_MODE)
            return;

        backgroundColor = newBackgroundColor;
        fontColor = newFontColor;
    }

    void setCursorPos(int row, int col){
        if( inBounds(row, col)){
            cursorRow = row;
            cursorCol = col;
        }
    }
//End Setters

//Special characters
    static void tab(){

        if(cursorCol + 4 >= screenWidth)
            cursorCol = screenWidth - 1;
        else 
            cursorCol += 4;
    }

    static void enter(){
        if(cursorRow + 1 >= screenHeight){ //si al hacer el enter esta en la ultima linea, tienne que subir la pantalla
            scrollDownOnce();
            setCursorPos(screenHeight - 1, 0);
        } else
            setCursorPos(cursorRow + 1, 0);
    }

    static void backspace(){
        if(cursorRow == 0 && cursorCol == 0)
            return;  

        if(cursorCol <= 0){
            setCursorPos(cursorRow - 1, screenWidth - 1);
            printChar(' ');
            setCursorPos(cursorRow - 1, screenWidth - 1);
        }else{
            cursorCol--;
            printChar(' ');
            cursorCol--;
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
        }
        return 1;
    }
//End Special characters

//Auxiliar functions
    void newLine(){
        printChar('\n');
    }
    //Vacia la pantalla y lo deja en el formato default
    void clearScreen(){
        setCursorPos(0, 0);
        for (int i = 0; i < screenHeight * screenWidth; i++){
            printFormatedChar(' ', DEFAULT_BACKGROUND_COLOR, DEFAULT_FONT_COLOR);
        }
        setCursorPos(0, 0);
    }

    static void scrollDownOnce(){
        
        for (int y = 0; y < screenHeight - CHAR_HEIGHT; y++){
            for (int x = 0; x < screenWidth; x++){
                copyPixel(x, y + CHAR_HEIGHT, x, y);
            }
        }

        int cursorRowBackup = cursorRow;
        int cursorColBackup = cursorCol;

        setCursorPos( screenHeight - 1, 0);
        
        for (int i = 0; i < screenWidth; i++){
            printChar(' ');
        }
        setCursorPos(cursorRowBackup,cursorColBackup);
    }

    static int inBounds(int row, int col){
        return row >= 0 && row < screenHeight && col >= 0 && col < screenWidth;
    }    
//End auxiliar

//Print Numbers
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
//End Print Numbers