#include "pic.h"
#include "io.h"
#include "stdint.h"

void pic_remap_interrupts() {
	// master pic
	outb(0x20, 0x11); // init
	outb(0x21, 0x20); // interrupt no for IRQ0
	outb(0x21, 0x04); // IRQ 2 is slave
	outb(0x21, 0x01); // icw 4

	// slave pic
	outb(0xa0, 0x11); // init
	outb(0xa1, 0x28); // interrupt no for IRQ8
	outb(0xa1, 0x02); // IRQ 2 is slave
	outb(0xa1, 0x01); // icw 4

	// unmask all interrupts
	outb(0x21, 0x0);
	outb(0xa1, 0x0);
}
