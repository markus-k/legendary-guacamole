#include "console.h"

uint16_t cursor_x = 0;
uint16_t cursor_y = 0;
uint8_t color = 0x07;

void kclear() {
	uint8_t *video = (uint8_t *)CONSOLE_ADDR;
	int i;

	for (i = 0; i < 2 * CONSOLE_WIDTH * CONSOLE_HEIGHT; i++) {
		video[i] = 0x00;
	}
}

void kputc(char c) {
	uint8_t *video = (uint8_t *)CONSOLE_ADDR;

	video[2 * (cursor_y * CONSOLE_WIDTH + cursor_x)] = c;
	video[2 * (cursor_y * CONSOLE_WIDTH + cursor_x) + 1] = color;
}

void kprintf(char *str) {
	int i;

	for (i = 0; str[i] != '\0'; i++) {
		char c = str[i];

		switch (c) {
			case '\n':
				cursor_y++;
				cursor_x = 0;
				break;
			case '\r':
				cursor_x = 0;
				break;
			default:
				kputc(c);
				cursor_x++;
				if (cursor_x >= CONSOLE_WIDTH) {
					cursor_y++;
					cursor_x = 0;
				}
		}
	}
}
