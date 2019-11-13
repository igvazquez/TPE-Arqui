include ../Makefile.inc

MODULE=0000-sampleCodeModule.bin
MODULE_ELF=0000-sampleCodeModule.elf

SOURCES=$(wildcard [^_]*.c)

SOURCES_ASM = $(wildcard asm/*.asm)

OBJECTS_ASM = $(SOURCES_ASM:.asm=.o)

all: $(MODULE) $(MODULE_ELF)

$(MODULE): $(SOURCES) $(OBJECTS_ASM)
	$(GCC) $(GCCFLAGS) -T sampleCodeModule.ld  -I./include _loader.c $(OBJECTS_ASM) $(SOURCES) -o ../$(MODULE)

$(MODULE_ELF): $(SOURCES) $(OBJECTS_ASM)
	$(GCC) $(GCCFLAGS) -T sampleCodeModule.ld  -I./include _loader.c $(OBJECTS_ASM) $(SOURCES) -Wl --oformat=elf64-x86-64 -o ../$(MODULE_ELF)


%.o : %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -rf *.o asm/*.o 

.PHONY: all clean print
