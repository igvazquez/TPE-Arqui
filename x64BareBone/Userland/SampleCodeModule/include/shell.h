#include <stdLib.h>
#include <pcInfo.h>

#define LINE_MESSAGE "Grupo-Pija-Shell"
#define USER_INPUT_MAX_SIZE (SCREEN_WIDTH - strlen(LINE_MESSAGE) - 2)
#define END_SHELL_KEY ESC
#define CURSOR_COLOR 0x20

int startShell();