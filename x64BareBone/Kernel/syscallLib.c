#include <syscallLib.h>
#include <videoDriver.h>
#include <keyboardDriver.h>

void sysWriteToScreen(char * string, uint8_t row, uint8_t col){
    if(row>=VIDEO_VER_LEN || row<0 || col>= VIDEO_HOR_LEN || col< 0){
        return;
    }
    setCursorPos(row, col);
    printString(string);
}
char sysGetChar(){
   return getKey(); 
}


