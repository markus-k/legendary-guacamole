#ifndef _KERNEL_KBC_H
#define _KERNEL_KBC_H

#include "input.h"

#define KBC_IO_CMD	0x64
#define KBC_IO_DATA	0x60

void kbc_init();
void kbc_deinit();

#endif
