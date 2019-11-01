#include <stdLib.h>

char getCharAsm();
void write(char* string, unsigned char format);
void setCursorPosAsm(unsigned int row, unsigned int col);
void putChar(char c){
    char string[2] = {c, 0};
    write(string, 0x07);
}
char getChar(){
    return getCharAsm();
}
void setCursorPos(int row, int col){
    setCursorPosAsm(row, col);
}
void scanf(char * output, int n){
    char c;
    int counter=0;
    while((c=getChar())!='\n' && counter<n-1 ){
        if(c){
            putChar(c);
            if(c == '\b'){
                if(counter >= 1)
                    counter--;

            }else if(c == '\t')
                output[counter++]=' ';

            else
                output[counter++]=c;
        }
    }
    putChar('\n');
    output[counter]=0;   
}
void putCharf(char c, unsigned char format){
    char string[2] = {c, 0};
    write(string,format);
}
void printf(char * string, unsigned char format){
    write(string, format);
}
void println(char * string){
    write(string, 0x07);
    putChar('\n');
}

void print(char * string){
    write(string, 0x07);
}