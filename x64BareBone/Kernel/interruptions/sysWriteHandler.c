#include<syscall.h>
#include<stdint.h>


static uint8_t * const video = (uint8_t*)0xB8000;
static uint8_t * currentLine = (uint8_t*)0xB8000;
static const uint32_t width = 80;
static const uint32_t height = 25;

void sysWriteHandler(uint64_t fd, char * string){
    if(fd == 1){
        for (int i = 0; string[i]!=0; i++, currentLine+=2)
        {
            if(string[i]='\n')
                currentLine+=width* 2 - (currentLine-video)%width*2;
            else
                *currentLine=string[i];
        }  
    }
}
