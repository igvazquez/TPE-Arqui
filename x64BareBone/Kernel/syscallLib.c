#include <syscallLib.h>
#include <videoDriver.h>
#include <keyboardDriver.h>

void sysSetCursor(uint8_t row, uint8_t col){
    setCursorPos(row, col);
}
void sysWrite(char *string, unsigned char format){
    if (format<0 || format >LAST_COLOR_MODE)
        return;
    printFormatedString(string, format);
}

char sysGetChar(){
   return getKey(); 
}


