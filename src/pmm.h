#ifndef _KERNEL_PMM_H
#define _KERNEL_PMM_H

#include "multiboot.h"

void pmm_mark_used(void *ptr);
void *pmm_alloc();
void pmm_free(void *ptr);
void pmm_init(struct multiboot_info *mb_info);

#endif
