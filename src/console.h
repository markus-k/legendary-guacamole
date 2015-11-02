#ifndef _KERNEL_CONSOLE_H
#define _KERNEL_CONSOLE_H

#include "stdint.h"

#define CONSOLE_ADDR	0xb8000
#define CONSOLE_WIDTH	80
#define CONSOLE_HEIGHT	25

void kclear();
void kputc(char c);
void kprintf(char *str);

#endif
