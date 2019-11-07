#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <screenDriver.h>
#include <keyboardDriver.h>
#include <idtLoader.h>

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;

typedef int (*EntryPoint)();


void clearBSS(void * bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void * getStackBase()
{
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary()
{
	char buffer[10];
	setCursorPos(0,0);
	printString("[x64BareBones]");
	ncNewline();

	printString("CPU Vendor:");
	printString(cpuVendor(buffer));
	ncNewline();

	printString("[Loading modules]");
	ncNewline();
	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};

	loadModules(&endOfKernelBinary, moduleAddresses);
	printString("[Done]");
	ncNewline();
	ncNewline();

	printString("[Initializing kernel's binary]");
	ncNewline();

	clearBSS(&bss, &endOfKernel - &bss);

	printString("  text: 0x");
	ncPrintHex((uint64_t)&text);
	ncNewline();
	printString("  rodata: 0x");
	ncPrintHex((uint64_t)&rodata);
	ncNewline();
	printString("  data: 0x");
	ncPrintHex((uint64_t)&data);
	ncNewline();
	printString("  bss: 0x");
	ncPrintHex((uint64_t)&bss);
	ncNewline();

	printString("[Done]");
	ncNewline();
	ncNewline();
	return getStackBase();
}

int main()
{	
	load_idt();
	init_VM_Driver();

	printString("[Kernel Main]");
	ncNewline();
	printString("  Sample code module at 0x");
	ncPrintHex((uint64_t)sampleCodeModuleAddress);
	ncNewline();

	//ncClear();
	setCursorPos(0, 48);
	printChar('c');


	//int SampleCodeReturnValue = ((EntryPoint)sampleCodeModuleAddress)();

	//setColorMode(DEFAULT_BACKGROUND_COLOR, DEFAULT_TEXT_COLOR);
	//ncClear();

	// printString("  Calling the sample code module returned: ");
	// //ncPrintHex(SampleCodeReturnValue);
	// ncNewline();
	// ncNewline();

	// printString("  Sample data module at 0x");
	// ncPrintHex((uint64_t)sampleDataModuleAddress);
	// ncNewline();
	// printString("  Sample data module contents: ");
	// printString((char*)sampleDataModuleAddress);
	// ncNewline();

	// printString("[Finished]");

	return 0;
}
