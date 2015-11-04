.extern intr_common_handler
intr_common_handler:
	// save cpu state to stack
	push %ebp
	push %edi
	push %esi
	push %edx
	push %ecx
	push %ebx
	push %eax

	push %esp
	call handle_interrupt
	add $4, %esp

	pop %eax
	pop %ebx
	pop %ecx
	pop %edx
	pop %esi
	pop %edi
	pop %ebp

	// remove interrupt no and error code from stack
	add $8, %esp

	iret

.macro intr_stub no
.global intr_stub_\no
intr_stub_\no:
	push $0
	push $\no
	jmp intr_common_handler
.endm

.macro intr_stub_err no
.global intr_stub_\no
intr_stub_\no:
	push $\no
	jmp intr_common_handler
.endm

// exceptions
intr_stub 0
intr_stub 1
intr_stub 2
intr_stub 3
intr_stub 4
intr_stub 5
intr_stub 6
intr_stub 7
intr_stub 8
intr_stub_err 9
intr_stub_err 10
intr_stub_err 11
intr_stub_err 12
intr_stub_err 13
intr_stub_err 14
intr_stub 15
intr_stub 16
intr_stub_err 17
intr_stub 18

// IRQs
intr_stub 32
intr_stub 33
intr_stub 34
intr_stub 35
intr_stub 36
intr_stub 37
intr_stub 38
intr_stub 39
intr_stub 40
intr_stub 41
intr_stub 42
intr_stub 43
intr_stub 44
intr_stub 45
intr_stub 46
intr_stub 47

// syscall
intr_stub 48
