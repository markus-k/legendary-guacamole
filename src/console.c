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

	switch (c) {
		case '\n':
			cursor_y++;
			cursor_x = 0;
			break;
		case '\r':
			cursor_x = 0;
			break;
		default:
			video[2 * xyoffset(cursor_x, cursor_y)] = c;
			video[2 * xyoffset(cursor_x, cursor_y) + 1] = color;
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

void kputs(char *str) {
	char c;
	while ((c = *str++) != '\0') {
		kputc(c);
	}
}

void kputi(uint32_t val, uint8_t base) {
	static const char *chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int i = 0;
	char buf[32];

	while (val) {
		uint32_t rem = val % base;
		buf[i] = chars[rem];
		val = val / base;
		i++;
	}

	while (i--) {
		kputc(buf[i]);
	}
}

void kprintf(char *str, ...) {
	va_list ap;
	int i;

	va_start(ap, str);

	for (i = 0; str[i] != '\0'; i++) {
		char c = str[i];

		if (c == '%' && str[i + 1] != '\0') {
			char nextc = str[i + 1];

			switch (nextc) {
				case '%':
					kputc('%');
					break;
				case 'c':
					kputc((char)va_arg(ap, int));
					break;
				case 's':
					kputs(va_arg(ap, char *));
					break;
				case 'd':
					kputi(va_arg(ap, int), 10);
					break;
				case 'x':
					kputi(va_arg(ap, int), 16);
					break;
			}
			i++; // we already read the next char, so i++
		} else {
			kputc(c);
		}
	}

	va_end(ap);
}

void kscroll() {
	uint8_t *video = (uint8_t *)CONSOLE_ADDR;
	uint8_t *video_row2 = video + 2 * xyoffset(0, 1);

	memmove(video, video_row2, 2 * CONSOLE_WIDTH * (CONSOLE_HEIGHT - 1));
	memset(video + 2 * xyoffset(0, CONSOLE_HEIGHT - 1), 0x00, 2 * CONSOLE_WIDTH);
}
