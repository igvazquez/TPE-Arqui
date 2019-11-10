include ../Makefile.inc

MODULE=0000-sampleCodeModule.bin

SOURCES=$(wildcard [^_]*.c)
SOURCES_ASM=$(wildcard asm/*.asm)

OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)

SOURCES_ASM = $(wildcard asm/*.asm)

OBJECTS_ASM = $(SOURCES_ASM:.asm=.o)

all: $(MODULE)

$(MODULE): $(SOURCES) $(OBJECTS_ASM)
	$(GCC) $(GCCFLAGS) -T sampleCodeModule.ld _loader.c  -I ./include $(OBJECTS_ASM) $(SOURCES) -o ../$(MODULE)

%.o : %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -rf *.o asm/*.o

.PHONY: all clean print
