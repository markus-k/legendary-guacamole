#include "console.h"

void init() {
	kclear();
	kprintf("Hello World.\n");
	kprintf("Now starting up\n");

	while (1);
}
