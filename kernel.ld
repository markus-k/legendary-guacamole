ENTRY(start)

SECTIONS
{
	/* load kernel at 3GB + 1MB */
	. = 0xC0100000;

	kernel_start = . - 0xC0000000;

	.text : AT(ADDR(.text) - 0xC0000000) {
		*(multiboot)
		*(.text)
	}
	.data ALIGN(4096) : AT(ADDR(.data) - 0xC0000000) {
		*(.data)
	}
	.rodata ALIGN(4096) : AT(ADDR(.rodata) - 0xC0000000) {
		*(.rodata)
	}
	.bss ALIGN(4096) : AT(ADDR(.bss) - 0xC0000000) {
		*(.bss)
	}

	kernel_end = . - 0xC0000000;
}
