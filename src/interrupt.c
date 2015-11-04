#include "interrupt.h"
#include "io.h"
#include "console.h"

void handle_interrupt(struct cpu_state *cpu) {
	if (cpu->intr >= 0x20 && cpu->intr <= 0x2f) {
		if (cpu->intr >= 0x28) {
			outb(0xa0, 0x20);
		}
		outb(0x20, 0x20);
	}
}
