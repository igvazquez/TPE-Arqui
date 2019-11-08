#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <screenDriver.h>
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

void clearBSS(void * bssAddress, uint64_t bssSize){
	memset(bssAddress, 0, bssSize);
}

void * getStackBase(){
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary(){
	char buffer[10];

	printString("[x64BareBones]");
	newLine();

	printString("CPU Vendor:");
	printString(cpuVendor(buffer));
	newLine();

	printString("[Loading modules]");
	newLine();
	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};

	loadModules(&endOfKernelBinary, moduleAddresses);
	printString("[Done]");
	newLine();
	newLine();

	printString("[Initializing kernel's binary]");
	newLine();

	clearBSS(&bss, &endOfKernel - &bss);

	printString("  text: 0x");
	ncPrintHex((uint64_t)&text);
	newLine();
	printString("  rodata: 0x");
	ncPrintHex((uint64_t)&rodata);
	newLine();
	printString("  data: 0x");
	ncPrintHex((uint64_t)&data);
	newLine();
	printString("  bss: 0x");
	ncPrintHex((uint64_t)&bss);
	newLine();

	printString("[Done]");
	newLine();
	newLine();
	return getStackBase();
}

int main(){	
	load_idt();
	initializeScreenDriver();
	printString("[Kernel Main]");
	newLine();
	printString("  Sample code module at 0x");
	ncPrintHex((uint64_t)sampleCodeModuleAddress);
	newLine();
	printString("  Calling the sample code module returned: ");
	ncPrintHex(((EntryPoint)sampleCodeModuleAddress)());
	newLine();
	newLine();

	printString("  Sample data module at 0x");
	ncPrintHex((uint64_t)sampleDataModuleAddress);
	newLine();
	printString("  Sample data module contents: ");
	printString((char*)sampleDataModuleAddress);
	newLine();

	printString("[Finished]\n");
	return 0;
}
