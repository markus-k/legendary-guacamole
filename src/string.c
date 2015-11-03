#include "string.h"

void memset(void *ptr, uint8_t val, size_t len) {
	while (len--) {
		*(uint8_t *)(ptr++) = val;
	}
}

void memmove(void *dst, void *src, size_t len) {
	if (dst == src || len == 0) {
		return;
	}

	if (src > dst) {
		while (len--) {
			*(uint8_t *)dst++ = *(uint8_t *)src++;
		}
	} else {
		dst += len;
		src += len;
		while (len--) {
			*(uint8_t *)dst-- = *(uint8_t *)src--;
		}
	}
}

size_t strlen(char *str) {
	size_t len = 0;
	while (*(str++) != '\0') {
		len++;
	}
	return len;
}
