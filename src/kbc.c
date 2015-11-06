#include "kbc.h"
#include "io.h"
#include "interrupt.h"
#include "stdint.h"
#include "console.h"

#define KBC_STATUS_OUT_FULL	(1 << 0)
#define KBC_STATUS_IN_FULL	(1 << 1)
#define KBC_STATUS_SELFTEST	(1 << 2)
#define KBC_STATUS_LASTPORT	(1 << 3)
#define KBC_STATUS_KB_LOCKED	(1 << 4)
#define KBC_STATUS_PSAUX	(1 << 5)
#define KBC_STATUS_TIMEOUT	(1 << 6)
#define KBC_STATUS_PARITYERR	(1 << 7)

#define KBC_CMD_ACTIVATE	0xF4

struct keycodemap_item {
	uint16_t scancode;
	uint8_t keycode;
};

#define KEYCODEMAP_ITEM(s, k) {.scancode = (s), .keycode = (k)}

// map for standard scancodes
// not complete yet
struct keycodemap_item keycodemap_default[] = {
	KEYCODEMAP_ITEM(0x01, KEY_ESC),
	KEYCODEMAP_ITEM(0x02, KEY_1),
	KEYCODEMAP_ITEM(0x03, KEY_2),
	KEYCODEMAP_ITEM(0x04, KEY_3),
	KEYCODEMAP_ITEM(0x05, KEY_4),
	KEYCODEMAP_ITEM(0x06, KEY_5),
	KEYCODEMAP_ITEM(0x07, KEY_6),
	KEYCODEMAP_ITEM(0x08, KEY_7),
	KEYCODEMAP_ITEM(0x09, KEY_8),
	KEYCODEMAP_ITEM(0x0A, KEY_9),
	KEYCODEMAP_ITEM(0x0B, KEY_0),
	KEYCODEMAP_ITEM(0x0C, KEY_MINUS),
	KEYCODEMAP_ITEM(0x0D, KEY_EQUAL),
	KEYCODEMAP_ITEM(0x0E, KEY_BACKSPACE),
	KEYCODEMAP_ITEM(0x10, KEY_Q),
	KEYCODEMAP_ITEM(0x11, KEY_W),
	KEYCODEMAP_ITEM(0x12, KEY_E),
	KEYCODEMAP_ITEM(0x13, KEY_R),
	KEYCODEMAP_ITEM(0x14, KEY_T),
	KEYCODEMAP_ITEM(0x15, KEY_Y),
	KEYCODEMAP_ITEM(0x16, KEY_U),
	KEYCODEMAP_ITEM(0x17, KEY_I),
	KEYCODEMAP_ITEM(0x18, KEY_O),
	KEYCODEMAP_ITEM(0x19, KEY_P),
	KEYCODEMAP_ITEM(0x1A, KEY_LEFTBRACE),
	KEYCODEMAP_ITEM(0x1B, KEY_RIGHTBRACE),
	KEYCODEMAP_ITEM(0x1C, KEY_ENTER),
	KEYCODEMAP_ITEM(0x1D, KEY_LEFTCTRL),
	KEYCODEMAP_ITEM(0x1E, KEY_A),
	KEYCODEMAP_ITEM(0x1F, KEY_S),
	KEYCODEMAP_ITEM(0x20, KEY_D),
	KEYCODEMAP_ITEM(0x21, KEY_F),
	KEYCODEMAP_ITEM(0x22, KEY_G),
	KEYCODEMAP_ITEM(0x23, KEY_H),
	KEYCODEMAP_ITEM(0x24, KEY_J),
	KEYCODEMAP_ITEM(0x25, KEY_K),
	KEYCODEMAP_ITEM(0x26, KEY_L),
	KEYCODEMAP_ITEM(0x27, KEY_SEMICOLON),
	KEYCODEMAP_ITEM(0x28, KEY_APOSTROPHE),
	KEYCODEMAP_ITEM(0x29, KEY_GRAVE),

	KEYCODEMAP_ITEM(0x2A, KEY_LEFTSHIFT),
	KEYCODEMAP_ITEM(0x2B, KEY_BACKSLASH),

	KEYCODEMAP_ITEM(0x2C, KEY_Z),
	KEYCODEMAP_ITEM(0x2D, KEY_X),
	KEYCODEMAP_ITEM(0x2E, KEY_C),
	KEYCODEMAP_ITEM(0x2F, KEY_V),
	KEYCODEMAP_ITEM(0x30, KEY_B),
	KEYCODEMAP_ITEM(0x31, KEY_N),
	KEYCODEMAP_ITEM(0x32, KEY_M),
	KEYCODEMAP_ITEM(0x33, KEY_COMMA),
	KEYCODEMAP_ITEM(0x34, KEY_DOT),
	KEYCODEMAP_ITEM(0x35, KEY_SLASH),
	KEYCODEMAP_ITEM(0x36, KEY_RIGHTSHIFT),

	KEYCODEMAP_ITEM(0x37, KEY_KPASTERISK),
	KEYCODEMAP_ITEM(0x38, KEY_LEFTALT),
	KEYCODEMAP_ITEM(0x39, KEY_SPACE),
	KEYCODEMAP_ITEM(0x3A, KEY_CAPSLOCK),
	KEYCODEMAP_ITEM(0x3B, KEY_F1),
	KEYCODEMAP_ITEM(0x3C, KEY_F2),
	KEYCODEMAP_ITEM(0x3D, KEY_F3),
	KEYCODEMAP_ITEM(0x3E, KEY_F4),
	KEYCODEMAP_ITEM(0x3F, KEY_F5),
	KEYCODEMAP_ITEM(0x40, KEY_F6),
	KEYCODEMAP_ITEM(0x41, KEY_F7),
	KEYCODEMAP_ITEM(0x42, KEY_F8),
	KEYCODEMAP_ITEM(0x43, KEY_F9),
	KEYCODEMAP_ITEM(0x44, KEY_F10),

	KEYCODEMAP_ITEM(0x4B, KEY_LEFT),
	KEYCODEMAP_ITEM(0x4D, KEY_RIGHT),
	KEYCODEMAP_ITEM(0x48, KEY_UP),
	KEYCODEMAP_ITEM(0x50, KEY_DOWN),

	KEYCODEMAP_ITEM(0x57, KEY_F11),
	KEYCODEMAP_ITEM(0x58, KEY_F12),
};
const size_t keycodemap_default_len = sizeof(keycodemap_default);

static inline uint8_t kbc_read_status() {
	return inb(KBC_IO_CMD);
}

static inline void kbc_wait_write() {
	while (!(kbc_read_status() & KBC_STATUS_IN_FULL));
}

void kbc_send_cmd(uint8_t cmd) {
	kbc_wait_write();
	outb(KBC_IO_CMD, cmd);
}

uint8_t kbc_read_data() {
	return inb(KBC_IO_DATA);
}

#define SCANCODE_TYPE_DEFAULT	0
#define SCANCODE_TYPE_E0	1
#define SCANCODE_TYPE_E1	2

uint8_t translate_scancode(uint8_t type, uint16_t scancode) {
	struct keycodemap_item *map = keycodemap_default;
	size_t map_len = keycodemap_default_len;
	struct keycodemap_item *item = map;

	if (type == SCANCODE_TYPE_E0) {
	} else if (type == SCANCODE_TYPE_E1) {
	}

	while (item < map + map_len) {
		if (item->scancode == scancode) {
			return item->keycode;
		}
		item++;
	}

	return 0;
}

void handle_kbc_irq() {
	uint8_t keystate = 0;
	uint8_t keycode = 0;
	uint8_t scancode = 0;

	static uint8_t e0 = 0;
	static uint8_t e1 = 0;
	static uint8_t e1_first = 0;

	if (!(kbc_read_status() & KBC_STATUS_OUT_FULL)) {
		kprintf("kbc: got kbc irq but no data\n");
		return;
	}

	scancode = kbc_read_data();

	if (scancode & 0x80 && (e0 || scancode != 0xE0) && (e1 || scancode != 0xE1)) {
		scancode &= ~0x80;
		keystate = 1;
	}

	if (e0) {
		if (scancode == 0x2A || scancode == 0x36) {
			// catch 'fake shifts'
			e0 = 0;
		}
		e0 = 0;
		keycode = translate_scancode(SCANCODE_TYPE_E0, scancode);
	} else if (e1 == 1) {
		e1_first = scancode;
		e1++;
	} else if (e1 == 2) {
		keycode = translate_scancode(SCANCODE_TYPE_E1, (uint16_t)e1_first | ((uint16_t)scancode << 8));
		e1 = 0;
	} else if (scancode == 0xE0) {
		// beginning of e0 code
		e0 = 1;
	} else if (scancode == 0xE1) {
		// beginning of e1 code
		e1 = 1;
	} else {
		// normal scancode
		keycode = translate_scancode(SCANCODE_TYPE_DEFAULT, scancode);
	}

	kprintf("scancode: 0x%x\n", scancode);
	kprintf("Keycode: %d", keycode);
}

void kbc_cpu_reset() {
	kbc_wait_write();
	kbc_send_cmd(0xD1);
	kbc_wait_write();
	kbc_send_cmd(0xFE);
}

void kbc_init() {
	register_irq_handler(1, handle_kbc_irq);

	// empty input buffer
	while (kbc_read_status() & KBC_STATUS_OUT_FULL) {
		kbc_read_data();
	}

	kprintf("Activating keyboard\n");
	kbc_send_cmd(KBC_CMD_ACTIVATE);
}

void kbc_deinit() {
	unregister_irq_handler(1);
}
