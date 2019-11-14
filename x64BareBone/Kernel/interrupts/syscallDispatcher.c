//syscallDispatcher.c

#include <stdint.h>
#include <timerTick.h>
#include <lib.h>
#include <screenDriver.h>
#include <defs.h>
#include <videoDriver.h>
#include <keyboardDriver.h>
#include <interrupts.h>
#include <soundDriver.h>

int syscallDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx){
	switch (rdi){
        //SysCall 0: cuantos ticks pasaron. No recibe parametros.
        case 0:
            return ticks_elapsed();
        
        //SysCall 1: cantidad de pixeles de alto de la pantalla
        case 1:
            return getVerticalPixelCount();
            break;

        //SysCall 2: cantidad de pixeles de ancho de la pantalla
        case 2:
            return getHorizontalPixelCount();
            break;
        //SysCall 3: devuelve la primer letra del buffer.
        case 3:
            return getKey();
       
        //SysCall 4 : imprime un string con formato.
        //RBX   /  RSI : puntero al string. Terminado en "\0"
        //RCX   /   RDX : color de fondo
        //RDX   /   RCX : color de la letra
        case 4:
            printFormatedString((char*)rsi, rdx, rcx);
            break;

        //SysCall 5: imprime el contenido de todos lo registros. No recibe parametros
        case 5:
            printRegisters();
            break;

        //SysCall 6: pinta el pixel (x,y) con un color en HEXA
        //RBX   /  RSI : x
        //RCX   /   RDX : y
        //RDX   /   RCX : color
        case 6:
            drawPixel(rsi, rdx, rcx);
            break;

        //SysCall 7: ubica el cursor para el SysCall 4
        //RBX   /  RSI : row
        //RCX   /   RDX : col
        case 7:
            setCursorPos(rsi, rdx); 
            break;
        //SysCall 8: devuelve la hora, minutos o segundos del reloj
        //RBX   /  RSI : timeID : minutos hora o segundos
        case 8:
            return sysRTC(rsi); 
        //SysCall 9: Hace un beep.
        case 9:  
            beep();
            return 1;
    }
    return 0;
}