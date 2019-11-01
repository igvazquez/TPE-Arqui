#include <syscallLib.h>

void sysWrite(uint64_t fd, char * string){
    if(fd == STDOUT)
        printString(string);

    else if(fd == STDOUT){
    	printFormatedString(string, ERROR_COLOR_MODE);
    }
}
