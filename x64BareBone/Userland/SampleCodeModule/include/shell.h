#include <stdLib.h>
#include <pcInfo.h>

#define LINE_MESSAGE "Fleshy-Shell"
#define USER_INPUT_MAX_SIZE (SCREEN_WIDTH - strlen(LINE_MESSAGE) - 2)
#define END_SHELL_KEY ESC
#define CURSOR_COLOR 0x20

#define FUNCTION_NUMBER 20

int startShell();