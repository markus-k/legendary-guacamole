#ifndef _KERNEL_PIC_H
#define _KERNEL_PIC_H

#define PIC_IO_MASTER_CMD	0x20
#define PIC_IO_MASTER_DATA	0x21
#define PIC_IO_SLAVE_CMD	0xA0
#define PIC_IO_SLAVE_DATA	0xA1

void pic_remap_interrupts();

#endif
