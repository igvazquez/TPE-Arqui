#include <stdint.h>
#include <defs.h>
#include <videoDriver.h>
#include <keyboardDriver.h>
#include <syscallLib.h>

int syscallDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx) {
	switch (rdi){
        case 3:
            return getKey();
        case 4:
            sysWrite((char*)rsi, rdx);
            break;
        case 7:
            setCursorPos(rsi, rdx);
            break;
    
    }
    return 0;
}