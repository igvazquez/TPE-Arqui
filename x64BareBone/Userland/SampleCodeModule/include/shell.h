//shell.h
#ifndef __SHELL_H__
#define __SHELL_H__

#include <stdLib.h>
#include <arcanoid.h>
#define ESC 27
#define TICKS_PER_SECOND 18
#define LINE_MESSAGE "Fleshy-Shell"
#define USER_INPUT_MAX_SIZE 50
#define END_SHELL_KEY ESC
#define CURSOR_COLOR 0x00FF00

#define FUNCTION_NUMBER 20

int startShell();

#endif
