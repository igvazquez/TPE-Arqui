include Makefile.inc

KERNEL = kernel.bin
KERNEL_ELF = kernel.elf

SOURCES=$(wildcard *.c)
SOURCES_DRIVERS=$(wildcard drivers/*.c)
SOURCES_INTERRUPTS=$(wildcard interrupts/*.c)

SOURCES_ASM=$(wildcard asm/*.asm)
SOURCES_DRIVERS_ASM=$(wildcard drivers/*.asm)
SOURCES_INTERRUPTS_ASM=$(wildcard interrupts/*.asm)

OBJECTS=$(SOURCES:.c=.o)
OBJECTS_DRIVERS=$(SOURCES_DRIVERS:.c=.o)
OBJECTS_INTERRUPTS=$(SOURCES_INTERRUPTS:.c=.o)

OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)
OBJECTS_DRIVERS_ASM=$(SOURCES_DRIVERS_ASM:.asm=.o)
OBJECTS_INTERRUPTS_ASM=$(SOURCES_INTERRUPTS_ASM:.asm=.o)

ALLOBJECTS = $(LOADEROBJECT) $(OBJECTS) $(OBJECTS_ASM) $(OBJECTS_DRIVERS) $(OBJECTS_DRIVERS_ASM) $(OBJECTS_INTERRUPTS) $(OBJECTS_INTERRUPTS_ASM)

LOADERSRC=loader.asm

LOADEROBJECT=$(LOADERSRC:.asm=.o)
STATICLIBS=

all: $(KERNEL) $(KERNEL_ELF)

$(KERNEL):  $(STATICLIBS) $(ALLOBJECTS)
	$(LD) $(LDFLAGS) -T kernel.ld -o $(KERNEL) $(ALLOBJECTS) $(STATICLIBS)

$(KERNEL_ELF):  $(STATICLIBS) $(ALLOBJECTS)
	$(LD) $(LDFLAGS) -T kernel.ld -o $(KERNEL_ELF) --oformat=elf64-x86-64 $(ALLOBJECTS) $(STATICLIBS)

%.o: %.c
	$(GCC) $(GCCFLAGS) -I./include  -I./drivers/include -I./interrupts/include -c $< -o $@

%.o : %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -rf asm/*.o *.o *.bin drivers/*.o interrupts/*.o

.PHONY: all clean
