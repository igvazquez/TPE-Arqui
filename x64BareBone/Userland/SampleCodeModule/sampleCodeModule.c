#include <stdLib.h>

int main() {
	//All the following code may be removed 
/*	
	char c;

	while (c = getChar())
	{
		putChar(c);
	}
	*/
	char output[20];
	scanf(output, 20);

	print(output);
	setCursorPos(5, 8);
	print(output);
	setCursorPos(0,0);
	print(output);

	//Test if BSS is properly set up
	return 0;
}