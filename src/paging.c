#include "stdint.h"
#include "pageframe.h"

#define PAGEDIR_FLAG_SIZE       0x40
#define PAGEDIR_FLAG_ACCESSED   0x20
#define PAGEDIR_FLAG_NOCACHE    0x10
#define PAGEDIR_FLAG_WRITETHRU  0x08
#define PAGEDIR_FLAG_USER       0x04
#define PAGEDIR_FLAG_WRITEABLE  0x02
#define PAGEDIR_FLAG_PRESENT    0x01

#define PAGEDIR_ENTRIES         1024

struct pagedir_entry {
	uint32_t flags : 9;
	uint32_t avail : 3;
	uint32_t addr : 20;
};

#define PAGETBL_FLAG_GLOBAL     0x80
#define PAGETBL_FLAG_DIRTY      0x40
#define PAGETBL_FLAG_ACCESSED   0x20
#define PAGETBL_FLAG_NOCACHE    0x10
#define PAGETBL_FLAG_WRITETHRU  0x08
#define PAGETBL_FLAG_USER       0x04
#define PAGETBL_FLAG_WRITEABLE  0x02
#define PAGETBL_FLAG_PRESENT    0x01

#define PAGETBL_ENTRIES         1024

struct pagetbl_entry {
	uint32_t flags : 9;
	uint32_t avail : 3;
	uint32_t addr : 20;
};

// page directory with 1024 entries
struct pagedir_entry *page_directory;

// first page table
struct pagetbl_entry *first_pagetable;

void create_page_directory() {
	// allocate 4096b aligned page directory
	page_directory = pfa_alloc();

	for (int i = 0; i < PAGEDIR_ENTRIES; i++) {
		page_directory[i].addr = 0;
		page_directory[i].avail = 0;
		page_directory[i].flags = PAGEDIR_FLAG_WRITEABLE;
	}
}

void create_first_pagetable() {
	// allocate 4096b aligned page table
	first_pagetable = pfa_alloc();

	// identity map the first 4 megabytes (1:1 map)
	for (int i = 0; i < PAGETBL_ENTRIES; i++) {
		first_pagetable[i].addr = i * 0x1000;
		first_pagetable[i].flags = PAGETBL_FLAG_WRITEABLE | PAGETBL_FLAG_PRESENT;
	}

	page_directory[0].addr = (uint32_t)first_pagetable;
	page_directory[0].avail = 0;
	page_directory[0].flags = PAGEDIR_FLAG_WRITEABLE | PAGEDIR_FLAG_PRESENT;
}

void load_page_directory() {
	// mov the page directory address to the cr3 register
	asm volatile("mov %0, %%cr3" : : "r" (page_directory));
}

void enable_paging() {
	register uint32_t cr0;
	asm volatile("mov %%cr0, %0" : "=r" (cr0));
	cr0 |= 0x8000000;
	asm volatile("mov %0, %%cr0" :: "r" (cr0));
}

void paging_init() {
	create_page_directory();
	create_first_pagetable();

	load_page_directory();
	enable_paging();
}
