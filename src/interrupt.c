#include "interrupt.h"
#include "io.h"
#include "pic.h"
#include "console.h"
#include "string.h"

irq_handler_fn irq_handlers[16];

void interrupts_enable() {
	asm volatile("sti");
}

int register_irq_handler(int irq, irq_handler_fn handler) {
	if (irq_handlers[irq] != NULL) {
		return IRQ_REG_ERR_INUSE;
	}
	irq_handlers[irq] = handler;

	return IRQ_REG_OK;
}

void unregister_irq_handler(int irq) {
	irq_handlers[irq] = NULL;
}

void handle_irq(struct cpu_state *cpu) {
	uint32_t irq = cpu->intr - 0x20;

	if (irq_handlers[irq] != NULL) {
		irq_handlers[irq]();
	}
}

void handle_interrupt(struct cpu_state *cpu) {
	if (cpu->intr >= 0x20 && cpu->intr <= 0x2f) {
		// send End Of Interrupt to corresponding PIC
		if (cpu->intr >= 0x28) {
			outb(PIC_IO_SLAVE_CMD, 0x20);
		}
		outb(PIC_IO_MASTER_CMD, 0x20);

		handle_irq(cpu);
	}

	//kprintf("Interrupt 0x%x ", cpu->intr);
}
