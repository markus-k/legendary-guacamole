#include "multiboot.h"
#include "pageframe.h"
#include "paging.h"
#include "console.h"
#include "gdt.h"
#include "idt.h"
#include "pic.h"
#include "kbc.h"

void init(struct multiboot_info *multiboot_info) {
	kclear();
	kprintf("Hello World.\n");
	kprintf("Now starting up.\n\n");

	pfa_init(multiboot_info);

	kprintf("Test: %s, %c, %d, 0x%x\n", "Teststr", '!', 1234567890, 49358);

	gdt_init();
	kprintf("GDT loaded\n");

	idt_init();
	kprintf("IDT loaded\n");

	pic_remap_interrupts();
	kprintf("PIC remapped\n");

	kprintf("Now enabling interrupts\n");
	asm volatile("sti");

	kprintf("Enabling paging\n");
	paging_init();

	kprintf("KBC init\n");
	kbc_init();

	while (1);
}
