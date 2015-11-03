#ifndef _KERNEL_STRING_H
#define _KERNEL_STRING_H

#include "stdint.h"

void memset(void *ptr, uint8_t val, size_t len);
void memmove(void *dst, void *src, size_t len);

size_t strlen(char *str);

#endif
