#include <syscallLib.h>

void sysSetCursor(uint8_t row, uint8_t col){
    setCursorPos(row, col);
}
void sysWrite(char *string, unsigned int backgroundColor, unsigned int textColor){
    printFormatedString(string, backgroundColor, textColor);
}

char sysGetChar(){
   return getKey(); 
}


