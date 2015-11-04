#include "gdt.h"
#include "stdint.h"

#define GDT_FLAG_DATASEG	0x02
#define GDT_FLAG_CODESEG	0x0a
#define GDT_FLAG_TSS		0x09

#define GDT_FLAG_SEGMENT	0x10
#define GDT_FLAG_RING0		0x00
#define GDT_FLAG_RING3		0x60
#define GDT_FLAG_PRESENT	0x80

#define GDT_FLAG_4K_GRAN	0x800
#define GDT_FLAG_32_BIT		0x400

#define GDT_ENTRY_COUNT		5

struct gdt_pointer {
	uint16_t limit;
	void *pointer;
} __attribute__((packed));

uint64_t gdt[GDT_ENTRY_COUNT];
struct gdt_pointer gdtp = {
	.limit = GDT_ENTRY_COUNT * 8 - 1,
	.pointer = gdt
};

void gdt_set_entry(int i, uint32_t base, uint32_t limit, uint32_t flags) {
	gdt[i] = limit & 0xffffLL;
	gdt[i] |= (base & 0xffffffLL) << 16;
	gdt[i] |= (flags & 0xffLL) << 40;
	gdt[i] |= ((limit >> 16) & 0xfLL) << 48;
	gdt[i] |= ((flags >> 8) & 0xffLL) << 52;
	gdt[i] |= ((base >> 24) & 0xffLL) << 56;
}

void gdt_load() {
	asm volatile("lgdt %0" : : "m" (gdtp));
}

void gdt_init() {
#define MEM_4GB 0xffffffff
	gdt_set_entry(0, 0, 0, 0);
	gdt_set_entry(1, 0, MEM_4GB, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT | GDT_FLAG_CODESEG | GDT_FLAG_4K_GRAN | GDT_FLAG_PRESENT);
	gdt_set_entry(2, 0, MEM_4GB, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT | GDT_FLAG_DATASEG | GDT_FLAG_4K_GRAN | GDT_FLAG_PRESENT);
	gdt_set_entry(3, 0, MEM_4GB, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT | GDT_FLAG_CODESEG | GDT_FLAG_4K_GRAN | GDT_FLAG_PRESENT | GDT_FLAG_RING3);
	gdt_set_entry(4, 0, MEM_4GB, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT | GDT_FLAG_CODESEG | GDT_FLAG_4K_GRAN | GDT_FLAG_PRESENT | GDT_FLAG_RING3);

	gdt_load();
}

