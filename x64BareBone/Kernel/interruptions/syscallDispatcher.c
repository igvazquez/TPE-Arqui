#include <stdint.h>
#include <defs.h>
#include <videoDriver.h>
#include <syscallLib.h>

void syscallDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx) {
	switch (rdi){

        case 0:
            sysWrite(rsi, (char*)rdx);
            break;
    
    }
}