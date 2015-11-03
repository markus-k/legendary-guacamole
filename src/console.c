#include "console.h"
#include "string.h"

uint16_t cursor_x = 0;
uint16_t cursor_y = 0;
uint8_t color = 0x07;

#define xyoffset(x, y) ((y) * CONSOLE_WIDTH + (x))

void kclear() {
	memset((void *)CONSOLE_ADDR, 0x00, 2 * CONSOLE_WIDTH * CONSOLE_HEIGHT);
}

void kputc(char c) {
	uint8_t *video = (uint8_t *)CONSOLE_ADDR;

	if (cursor_x >= CONSOLE_WIDTH || cursor_y >= CONSOLE_HEIGHT) {
		// don't write off-screen.
		return;
	}

	video[2 * xyoffset(cursor_x, cursor_y)] = c;
	video[2 * xyoffset(cursor_x, cursor_y) + 1] = color;
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

		if (cursor_y >= CONSOLE_HEIGHT) {
			cursor_y = CONSOLE_HEIGHT - 1;
			kscroll();
		}

	}
}

void kscroll() {
	uint8_t *video = (uint8_t *)CONSOLE_ADDR;
	uint8_t *video_row2 = video + 2 * xyoffset(0, 1);

	memmove(video, video_row2, 2 * CONSOLE_WIDTH * (CONSOLE_HEIGHT - 1));
	memset(video + 2 * xyoffset(0, CONSOLE_HEIGHT - 1), 0x00, 2 * CONSOLE_WIDTH);
}
