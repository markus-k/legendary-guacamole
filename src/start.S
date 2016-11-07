.section multiboot

#define MB_MAGIC 0x1badb002
#define MB_FLAGS 0x0
#define MB_CHECKSUM -(MB_MAGIC + MB_FLAGS)

// multiboot header
.align 4
.int    MB_MAGIC
.int    MB_FLAGS
.int    MB_CHECKSUM



.section .data
// early page directory
#define KERNEL_PAGENUM		(KERNEL_BASE >> 22)
.align 0x1000
early_page_dir:
	// 0x83 => 4mb, writeable, present
	.int 0x00000083
	.space ((KERNEL_PAGENUM - 1) * 4)
	.int 0x00000083
	.space ((1024 - KERNEL_PAGENUM - 1) * 4)

.section .text
.extern init

.global start
.equ start, (_start - KERNEL_BASE)

.global _start
_start:
	// setup early paging

	// load early page dir address into cr3
	mov $early_page_dir - KERNEL_BASE, %eax
	mov %eax, %cr3

	// set PSE bit for large pages
	mov %cr4, %eax
	or $0x10, %eax
	mov %eax, %cr4

	// switch on paging
	mov %cr0, %eax
	or $0x80000000, %eax
	mov %eax, %cr0

	// long jump to higher address space
	lea (higher_half), %eax
	jmp *%eax

higher_half:
	// delete identity map of physical addresses at 0x00
	movl $0x0, (early_page_dir)
	invlpg (0)

	mov $kernel_stack, %esp
	add $KERNEL_BASE, %ebx
	push %ebx // push pointer to multiboot struct
	call init
loop:
	cli
	hlt
	jmp loop

// 8kb kernel stack
.section .bss
.space 8192
kernel_stack:
