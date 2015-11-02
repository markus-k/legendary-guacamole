BUILDDIR = build
OBJDIR = ${BUILDDIR}/obj
SRCDIR = src

SRCS = start.S main.c console.c
OBJS = $(addprefix ${OBJDIR}/,$(addsuffix .o,$(basename ${SRCS})))

KERNEL = ${BUILDDIR}/kernel

CC = gcc
LD = ld

ASFLAGS = -m32
CFLAGS = -m32 -Wall -fno-stack-protector -nostdinc -g
LDFLAGS = -melf_i386 -Ttext=0x100000

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
	rm -f ${OBJS}

.PHONY: clean
