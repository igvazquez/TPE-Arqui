#include <idtLoader.h>



DESCR_INT * idt = (DESCR_INT *) 0;	// IDT de 255 entradas

static void setup_IDT_entry (int index, uint64_t offset);

void load_idt() {

  //Excepcion division por 0
  setup_IDT_entry (0x00, (uint64_t) &_exception0Handler);

  //Excepcion codigo invalido
  setup_IDT_entry (0x06, (uint64_t) &_exception6Handler);

  //Interrupcion Timer Tick
  setup_IDT_entry (0x20, (uint64_t) &_irq00Handler); 

  //Interrupcion teclado
  setup_IDT_entry (0x21, (uint64_t) &_irq01Handler);

  //Interrupciones por software
  setup_IDT_entry (0x80, (uint64_t) &_syscallHandler);


	picMasterMask(0xFC); //Abro IRQ0 y IRQ1 del PIC
	picSlaveMask(0xFF);

  _sti();
}

static void setup_IDT_entry (int index, uint64_t offset) {
  idt[index].selector = 0x08;
  idt[index].offset_l = offset & 0xFFFF;
  idt[index].offset_m = (offset >> 16) & 0xFFFF;
  idt[index].offset_h = (offset >> 32) & 0xFFFFFFFF;
  idt[index].access = ACS_INT;
  idt[index].cero = 0;
  idt[index].other_cero = (uint64_t) 0;
}
