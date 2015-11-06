#include "pic.h"
#include "io.h"
#include "stdint.h"

void pic_remap_interrupts() {
	// master pic
	outb(PIC_IO_MASTER_CMD, 0x11); // init
	outb(PIC_IO_MASTER_DATA, 0x20); // interrupt no for IRQ0
	outb(PIC_IO_MASTER_DATA, 0x04); // IRQ 2 is slave
	outb(PIC_IO_MASTER_DATA, 0x01); // icw 4

	// slave pic
	outb(PIC_IO_SLAVE_CMD, 0x11); // init
	outb(PIC_IO_SLAVE_DATA, 0x28); // interrupt no for IRQ8
	outb(PIC_IO_SLAVE_DATA, 0x02); // IRQ 2 is slave
	outb(PIC_IO_SLAVE_DATA, 0x01); // icw 4

	// unmask all interrupts
	outb(PIC_IO_MASTER_DATA, 0x0);
	outb(PIC_IO_SLAVE_DATA, 0x0);
}
