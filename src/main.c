#include "console.h"
#include "gdt.h"
#include "idt.h"
#include "pic.h"

void init(void *multiboot_info) {
	kclear();
	kprintf("Hello World.\n");
	kprintf("Now starting up\n\n");

	gdt_init();
	kprintf("GDT loaded\n");

	idt_init();
	kprintf("IDT loaded\n");

	pic_remap_interrupts();
	kprintf("PIC remapped\n");

	asm volatile("sti");

	while (1);
}
