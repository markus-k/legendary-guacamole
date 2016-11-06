#ifndef _KERNEL_PAGEFRAME_H
#define _KERNEL_PAGEFRAME_H

#define PFA_PAGESIZE	0x1000

#include "stdint.h"
#include "multiboot.h"

void pfa_mark_used(void *ptr);

void *pfa_alloc();

void pfa_free(void *ptr);

void pfa_init(struct multiboot_info *mb_info);

#endif
