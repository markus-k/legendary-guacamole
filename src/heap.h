#ifndef _KERNEL_HEAP_H
#define _KERNEL_HEAP_H

#include "stdint.h"

void heap_init();

void *kmalloc(size_t len);
void kfree(void *ptr);

#endif
