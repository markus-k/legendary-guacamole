.section multiboot

#define MB_MAGIC 0x1badb002
#define MB_FLAGS 0x0
#define MB_CHECKSUM -(MB_MAGIC + MB_FLAGS)

// multiboot header
.align 4
.int    MB_MAGIC
.int    MB_FLAGS
.int    MB_CHECKSUM

.section .text
.extern init

.global _start
_start:
	mov $kernel_stack, %esp
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
