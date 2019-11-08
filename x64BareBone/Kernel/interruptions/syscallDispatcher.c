#include <stdint.h>
#include <defs.h>
#include <screenDriver.h>
#include <videoDriver.h>
#include <keyboardDriver.h>
#include <syscallLib.h>
#include <time.h>

int syscallDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx){
	switch (rdi){
        case 0:
            return ticks_elapsed();
        case 1:
            return getScreenWidth()/CHAR_WIDTH;
            break;
        case 2:
            return getScreenHeight()/CHAR_HEIGHT;
            break;
        case 3:
            return getKey();
        case 4:
            printFormatedString((char*)rsi, rdx, rcx);
            break;
        case 5:
            printRegisters();
            break;
        case 6:
            drawPixel(rsi, rdx, rcx);
            break;
        case 7:
            setCursorPos(rdx, rsi); //Dados vuelta porque primero va x(rdx) y luego y(rsi)
            break;
        
    
    }
    return 0;
}