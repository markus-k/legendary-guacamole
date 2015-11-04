#include "idt.h"
#include "interrupt.h"
#include "stdint.h"

#define IDT_TYPE_INTERRUPT	0x6
#define IDT_TYPE_TRAP		0x7
#define IDT_TYPE_TASK		0x5

#define IDT_SEGTYPE_16_BIT	0
#define IDT_SEGTYPE_32_BIT	1

#define IDT_ENTRY_COUNT		256

struct idt_pointer {
	uint16_t limit;
	void *base;
} __attribute__((packed));

uint64_t idt[IDT_ENTRY_COUNT];
struct idt_pointer idtp = {
	.limit = IDT_ENTRY_COUNT * 8 - 1,
	.base = idt
};

void idt_set_entry(int i, uint32_t offset, uint16_t selector, uint8_t type, uint8_t seg_type, uint8_t present, uint8_t priv_lvl) {
	idt[i] = offset & 0xffffLL;
	idt[i] |= (selector & 0xffffLL) << 16;
	idt[i] |= (type & 0x7LL) << 40;
	idt[i] |= (seg_type & 0x1LL) << 43;
	idt[i] |= (priv_lvl & 0x2LL) << 45;
	if (present) {
		idt[i] |= (0x1LL << 47); // present flag
	}
	idt[i] |= ((offset >> 16) & 0xffffLL) << 48;
}

void idt_load() {
	asm volatile("lidt %0" : : "m" (idtp));
}

void idt_init() {
	idt_set_entry( 0, (uint32_t)intr_stub_0 , 0x8, IDT_TYPE_INTERRUPT, IDT_SEGTYPE_32_BIT, 1, 0);
	idt_set_entry( 1, (uint32_t)intr_stub_1 , 0x8, IDT_TYPE_INTERRUPT, IDT_SEGTYPE_32_BIT, 1, 0);
	idt_set_entry( 2, (uint32_t)intr_stub_2 , 0x8, IDT_TYPE_INTERRUPT, IDT_SEGTYPE_32_BIT, 1, 0);
	idt_set_entry( 3, (uint32_t)intr_stub_3 , 0x8, IDT_TYPE_INTERRUPT, IDT_SEGTYPE_32_BIT, 1, 0);
	idt_set_entry( 4, (uint32_t)intr_stub_4 , 0x8, IDT_TYPE_INTERRUPT, IDT_SEGTYPE_32_BIT, 1, 0);
	idt_set_entry( 5, (uint32_t)intr_stub_5 , 0x8, IDT_TYPE_INTERRUPT, IDT_SEGTYPE_32_BIT, 1, 0);
	idt_set_entry( 6, (uint32_t)intr_stub_6 , 0x8, IDT_TYPE_INTERRUPT, IDT_SEGTYPE_32_BIT, 1, 0);
	idt_set_entry( 7, (uint32_t)intr_stub_7 , 0x8, IDT_TYPE_INTERRUPT, IDT_SEGTYPE_32_BIT, 1, 0);
	idt_set_entry( 8, (uint32_t)intr_stub_8 , 0x8, IDT_TYPE_INTERRUPT, IDT_SEGTYPE_32_BIT, 1, 0);
	idt_set_entry( 9, (uint32_t)intr_stub_9 , 0x8, IDT_TYPE_INTERRUPT, IDT_SEGTYPE_32_BIT, 1, 0);
	idt_set_entry(10, (uint32_t)intr_stub_10, 0x8, IDT_TYPE_INTERRUPT, IDT_SEGTYPE_32_BIT, 1, 0);
	idt_set_entry(11, (uint32_t)intr_stub_11, 0x8, IDT_TYPE_INTERRUPT, IDT_SEGTYPE_32_BIT, 1, 0);
	idt_set_entry(12, (uint32_t)intr_stub_12, 0x8, IDT_TYPE_INTERRUPT, IDT_SEGTYPE_32_BIT, 1, 0);
	idt_set_entry(13, (uint32_t)intr_stub_13, 0x8, IDT_TYPE_INTERRUPT, IDT_SEGTYPE_32_BIT, 1, 0);
	idt_set_entry(14, (uint32_t)intr_stub_14, 0x8, IDT_TYPE_INTERRUPT, IDT_SEGTYPE_32_BIT, 1, 0);
	idt_set_entry(15, (uint32_t)intr_stub_15, 0x8, IDT_TYPE_INTERRUPT, IDT_SEGTYPE_32_BIT, 1, 0);
	idt_set_entry(16, (uint32_t)intr_stub_16, 0x8, IDT_TYPE_INTERRUPT, IDT_SEGTYPE_32_BIT, 1, 0);
	idt_set_entry(17, (uint32_t)intr_stub_17, 0x8, IDT_TYPE_INTERRUPT, IDT_SEGTYPE_32_BIT, 1, 0);
	idt_set_entry(18, (uint32_t)intr_stub_18, 0x8, IDT_TYPE_INTERRUPT, IDT_SEGTYPE_32_BIT, 1, 0);

	idt_set_entry(32, (uint32_t)intr_stub_32, 0x8, IDT_TYPE_INTERRUPT, IDT_SEGTYPE_32_BIT, 1, 0);
	idt_set_entry(33, (uint32_t)intr_stub_33, 0x8, IDT_TYPE_INTERRUPT, IDT_SEGTYPE_32_BIT, 1, 0);
	idt_set_entry(34, (uint32_t)intr_stub_34, 0x8, IDT_TYPE_INTERRUPT, IDT_SEGTYPE_32_BIT, 1, 0);
	idt_set_entry(35, (uint32_t)intr_stub_35, 0x8, IDT_TYPE_INTERRUPT, IDT_SEGTYPE_32_BIT, 1, 0);
	idt_set_entry(36, (uint32_t)intr_stub_36, 0x8, IDT_TYPE_INTERRUPT, IDT_SEGTYPE_32_BIT, 1, 0);
	idt_set_entry(37, (uint32_t)intr_stub_37, 0x8, IDT_TYPE_INTERRUPT, IDT_SEGTYPE_32_BIT, 1, 0);
	idt_set_entry(38, (uint32_t)intr_stub_38, 0x8, IDT_TYPE_INTERRUPT, IDT_SEGTYPE_32_BIT, 1, 0);
	idt_set_entry(39, (uint32_t)intr_stub_39, 0x8, IDT_TYPE_INTERRUPT, IDT_SEGTYPE_32_BIT, 1, 0);
	idt_set_entry(40, (uint32_t)intr_stub_40, 0x8, IDT_TYPE_INTERRUPT, IDT_SEGTYPE_32_BIT, 1, 0);
	idt_set_entry(41, (uint32_t)intr_stub_41, 0x8, IDT_TYPE_INTERRUPT, IDT_SEGTYPE_32_BIT, 1, 0);
	idt_set_entry(42, (uint32_t)intr_stub_42, 0x8, IDT_TYPE_INTERRUPT, IDT_SEGTYPE_32_BIT, 1, 0);
	idt_set_entry(43, (uint32_t)intr_stub_43, 0x8, IDT_TYPE_INTERRUPT, IDT_SEGTYPE_32_BIT, 1, 0);
	idt_set_entry(44, (uint32_t)intr_stub_44, 0x8, IDT_TYPE_INTERRUPT, IDT_SEGTYPE_32_BIT, 1, 0);
	idt_set_entry(45, (uint32_t)intr_stub_45, 0x8, IDT_TYPE_INTERRUPT, IDT_SEGTYPE_32_BIT, 1, 0);
	idt_set_entry(46, (uint32_t)intr_stub_46, 0x8, IDT_TYPE_INTERRUPT, IDT_SEGTYPE_32_BIT, 1, 0);
	idt_set_entry(47, (uint32_t)intr_stub_47, 0x8, IDT_TYPE_INTERRUPT, IDT_SEGTYPE_32_BIT, 1, 0);

	idt_set_entry(48, (uint32_t)intr_stub_48, 0x8, IDT_TYPE_INTERRUPT, IDT_SEGTYPE_32_BIT, 1, 0);

	idt_load();
}
