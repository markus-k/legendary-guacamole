#ifndef _KERNEL_CONSOLE_H
#define _KERNEL_CONSOLE_H

#include "stdint.h"
#include "stdarg.h"

#define CONSOLE_ADDR	0xb8000
#define CONSOLE_WIDTH	80
#define CONSOLE_HEIGHT	25
#define CONSOLE_SIZE	(2 * CONSOLE_WIDTH * CONSOLE_HEIGHT)

void kclear();
void kputc(char c);
void kputs(char *str);
void kputi(uint32_t val, uint8_t base);
void kprintf(char *str, ...);
void kscroll();

#endif
