BUILDDIR = build
OBJDIR = ${BUILDDIR}/obj
SRCDIR = src

SRCS = start.S main.c multiboot.c console.c string.c gdt.c idt.c interrupt.c intr.S pic.c pageframe.c kbc.c paging.c
OBJS = $(addprefix ${OBJDIR}/,$(addsuffix .o,$(basename ${SRCS})))

KERNEL = ${BUILDDIR}/kernel

CC = gcc
LD = ld

ASFLAGS = -m32 -DKERNEL_BASE=0xC0000000
CFLAGS = -m32 -Wall -fno-stack-protector -fno-builtin -fno-builtin-function -nostdinc --std=gnu99 -g -DKERNEL_BASE=0xC0000000
LDFLAGS = -melf_i386 -Tkernel.ld -g

all: ${BUILDDIR} ${OBJDIR} ${KERNEL}

${KERNEL}: ${OBJS}
	${LD} ${LDFLAGS} -o $@ $^

${OBJDIR}/%.o: ${SRCDIR}/%.c
	${CC} ${CFLAGS} -c -o $@ $^

${OBJDIR}/%.o: ${SRCDIR}/%.S
	${CC} ${ASFLAGS} -c -o $@ $^

${OBJDIR}: ${BUILDDIR}
	mkdir -p ${OBJDIR}

${BUILDDIR}:
	mkdir -p ${BUILDDIR}

clean:
	rm -f ${OBJS} ${KERNEL}

.PHONY: clean
