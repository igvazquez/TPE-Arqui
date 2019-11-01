#include <stdLib.h>

char getCharAsm();
void write(char* string, unsigned char format);

void putChar(char c){
    char string[2] = {c, 0};
    write(string, 0x07);
}
char getChar(){
    return getCharAsm();
}

void scanf(char * output, int n){
    char c;
    int counter=0;
    while((c=getChar())!='\n' && counter<n-1 ){
        if(c){
            putChar(c);
            output[counter++]=c;
        }
    }
    putChar('\n');
    output[counter]=0;   
}

void printf(char * string){
    write(string, 0x07);
}