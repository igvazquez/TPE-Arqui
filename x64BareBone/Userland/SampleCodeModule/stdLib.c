#include <stdLib.h>

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);
#define CHAR_WIDTH 8
#define CHAR_HEIGHT 16
#define DEFAULT_BACKGROUND_COLOR 0x000000 //Negro
#define DEFAULT_FONT_COLOR 0xFFFFFF //Blanco

//Print Numbers
    void ncPrintBin(uint64_t value){
        ncPrintBase(value, 2);
    }

    void ncPrintBase(uint64_t value, uint32_t base){
        char buffer[64] = { '0' };
        uintToBase(value, buffer, base);
        print(buffer);
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

    int bsdToInt(uint8_t input){
        return input / 16 * 10 + input % 16;
    }

//Print number

void putChar(char c){
    putCharf(c, DEFAULT_BACKGROUND_COLOR, DEFAULT_FONT_COLOR);
}

void putCharf(char c, unsigned int backgroundColor, unsigned int fontColor){
    char string[2] = {c, 0};
    write(string,backgroundColor, fontColor);
}

void print(char * string){
    printf(string, DEFAULT_BACKGROUND_COLOR, DEFAULT_FONT_COLOR);
}

void printf(char * string, unsigned int backgroundColor, unsigned int fontColor){
    write(string, backgroundColor, fontColor);
}

void println(char * string){
    print(string);
    putChar('\n');
}

void scanf(char * output, int n){
    char c;
    int counter=0;
    while(counter < n-1 && (c=getChar())!='\n'){
        if(c){

            if(c == '\b'){
                if(counter >= 1)
                    counter--;

            }else if(c == '\t')
                output[counter++]=' ';

            else
                output[counter++]=c;
        }
    }
    output[counter]=0;   
}

int strlen(char * s){
    int rta = 0;
    while(*s){
        rta++;
        s++;
    }
    return rta;
}

int strcmp(char * s1, char * s2){
    while(*s1 != 0 && *s2 != 0){

        if(*s1 == *s2){
            s1++;
            s2++;
        } else 
            return *s1 - *s2;
    }

    if(*s1 == 0 && *s2 == 0)
        return 0;

    else if(*s2 == 0)
        return 1;

    else 
        return -1;

}

int getScreenHeight(){
    return getVerticalPixelCount() / CHAR_HEIGHT;
}

int getScreenWidth(){
    return getHorizontalPixelCount() / CHAR_WIDTH;
}
