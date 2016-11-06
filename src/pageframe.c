/**
 * Page Frame Allocator
 *
 * Keeps track of reserverd and free physical memory pages.
 */

#include "pageframe.h"

// 4GB/(32*4096) = 32768 items
// 1 = free
// 0 = used
#define BITMAP_SIZE		32768
uint32_t pfa_bitmap[BITMAP_SIZE];

// kernel start and end from linker script
extern const void kernel_start;
extern const void kernel_end;

#define BITMAP_INDEX(ptr) ((uint32_t)(ptr) / (PFA_PAGESIZE * 32))
#define BITMAP_BITINDEX(ptr) (((uint32_t)(ptr) / PFA_PAGESIZE) % 32)
#define BITMAP_ADDR(i, j) (((i) * 32 + (j)) * PFA_PAGESIZE)

void pfa_mark_used(void *ptr) {
	pfa_bitmap[BITMAP_INDEX(ptr)] &= ~(1 << BITMAP_BITINDEX(ptr));
}

void *pfa_alloc() {
	uint32_t i, j;

	for (i = 0; i < BITMAP_SIZE; i++) {
		for (j = 0; j < 32; j++) {
			if (pfa_bitmap[i] & (1 << j)) {
				pfa_bitmap[i] &= ~(1 << j);
				return (void *)BITMAP_ADDR(i, j);
			}
		}
	}

	return NULL;
}

void pfa_free(void *ptr) {
	pfa_bitmap[BITMAP_INDEX(ptr)] |= (1 << BITMAP_BITINDEX(ptr));
}

void pfa_init(struct multiboot_info *mb_info) {
	struct multiboot_mmap *mmap = (struct multiboot_mmap *)mb_info->mbs_mmap_addr;
	struct multiboot_mmap *mmap_end = mmap + mb_info->mbs_mmap_length;

	// free memory defined as free by the bootloader
	while (mmap < mmap_end) {
		if (mmap->type == 1) {
			void *addr = (void *)(uint32_t)mmap->base;
			void *end = addr + mmap->len;

			while (addr < end) {
				pfa_free(addr);
				addr += PFA_PAGESIZE;
			}
		}
		mmap++;
	}

	// mark kernel as used
	void *kernel_addr = (void *)&kernel_start;
	while (kernel_addr < &kernel_end) {
		pfa_mark_used(kernel_addr);
		kernel_addr += PFA_PAGESIZE;
	}
}
