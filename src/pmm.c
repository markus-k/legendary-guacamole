#include "pmm.h"

// 4GB/(32*4096kb) = 32768 items
// 1 = free
// 0 = used
#define BITMAP_SIZE		32768
uint32_t pmm_bitmap[BITMAP_SIZE];

// kernel start and end from linker script
extern const void kernel_start;
extern const void kernel_end;

#define BITMAP_INDEX(ptr) ((uint32_t)(ptr) / (4096 * 32))
#define BITMAP_BITINDEX(ptr) (((uint32_t)(ptr) / 4096) % 32)
#define BITMAP_ADDR(i, j) (((i) * 32 + (j)) * 4096)

void pmm_mark_used(void *ptr) {
	pmm_bitmap[BITMAP_INDEX(ptr)] &= ~(1 << BITMAP_BITINDEX(ptr));
}

void *pmm_alloc() {
	uint32_t i, j;

	for (i = 0; i < BITMAP_SIZE; i++) {
		for (j = 0; j < 32; j++) {
			if (pmm_bitmap[i] & (1 << j)) {
				pmm_bitmap[i] &= ~(1 << j);
				return (void *)BITMAP_ADDR(i, j);
			}
		}
	}

	return NULL;
}

void pmm_free(void *ptr) {
	pmm_bitmap[BITMAP_INDEX(ptr)] |= (1 << BITMAP_BITINDEX(ptr));
}

void pmm_init(struct multiboot_info *mb_info) {
	struct multiboot_mmap *mmap = (struct multiboot_mmap *)mb_info->mbs_mmap_addr;
	struct multiboot_mmap *mmap_end = mmap + mb_info->mbs_mmap_length;

	// free memory defined as free by the bootloader
	while (mmap < mmap_end) {
		if (mmap->type == 1) {
			void *addr = (void *)(uint32_t)mmap->base;
			void *end = addr + mmap->len;

			while (addr < end) {
				pmm_free(addr);
				addr += 4096;
			}
		}
		mmap++;
	}

	// mark kernel as used
	void *kernel_addr = (void *)&kernel_start;
	while (kernel_addr < &kernel_end) {
		pmm_mark_used(kernel_addr);
		kernel_addr += 4096;
	}
}
