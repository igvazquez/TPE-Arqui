include Makefile.inc

KERNEL=kernel.bin

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


SOURCES_INT=$(wildcard interruptions/*.c)
OBJECTS_INT=$(SOURCES_INT:.c=.o)

LOADEROBJECT=$(LOADERSRC:.asm=.o)
STATICLIBS= 

all: $(KERNEL)

$(KERNEL): $(LOADEROBJECT) $(OBJECTS) $(STATICLIBS) $(OBJECTS_ASM) $(OBJECTS_INT) 
	$(LD) $(LDFLAGS) -T kernel.ld -o $(KERNEL) $(LOADEROBJECT) $(OBJECTS) $(OBJECTS_INT) $(OBJECTS_ASM) $(STATICLIBS)

%.o: %.c
	$(GCC) $(GCCFLAGS) -I ./include -c $< -o $@

%.o : %.asm
	$(ASM) $(ASMFLAGS) $< -o $@


$(LOADEROBJECT):
	$(ASM) $(ASMFLAGS) $(LOADERSRC) -o $(LOADEROBJECT)

clean:
	rm -rf asm/*.o *.o *.bin interruptions/*.o

.PHONY: all clean
