// sampleCodeModule.c
#include <shell.h>
#include <stdLib.h>

int main() {
	println("WELCOMEHOME");
	println("WELCOMEHOME");
	println("WELCOMEHOME");
	println("WELCOMEHOME");
	println("WELCOMEHOME");
	println("WELCOMEHOME");
	println("WELCOMEHOME");
	int height, width;
	height = getScreenHeight();
	width = getScreenWidth();
	ncPrintBase(getScreenWidth(),10);
	println("");
	ncPrintBase(getScreenHeight(),10);
	setCursorPos(0,0);
	// ncPrintBase(height,10);
	//println("");
	//drawPixel(150,300,1523);
	// ncPrintBase(width,10);
	// for (int i = 0; i < getScreenHeight() * getScreenWidth(); i++)
	// 	print(" ");
	ncPrintBase(getScreenWidth(),10);
	println("");
	ncPrintBase(getScreenHeight(),10);
	
	
	while(1){}
	return 1;
	// return startShell();
}