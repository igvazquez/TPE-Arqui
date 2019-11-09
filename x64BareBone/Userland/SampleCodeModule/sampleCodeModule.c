// sampleCodeModule.c
#include <stdLib.h>

static int var1 = 0;
static int var2 = 0;


int main() {
	
	int currentTick, lastTick = -10;
	print("hola terminal\n");
	drawPixel(0, 0, 0x00FF00);
	setCursorPos(0, 0);
	print("HOLA FAUS");
	setCursorPos(20, 10);
	print("SOY TOBI");

	
	if (var1 == 0 && var2 == 0)
		return 0xDEADC0DE;

	return 0xDEADBEEF;
}