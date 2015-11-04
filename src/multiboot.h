#ifndef _KERNEL_MULTIBOOT_H
#define _KERNEL_MULTIBOOT_H

#include "stdint.h"

struct multiboot_info {
	uint32_t mbs_flags;
	uint32_t mbs_mem_lower;
	uint32_t mbs_mem_upper;
	uint32_t mbs_bootdevice;
	uint32_t mbs_cmdline;
	uint32_t mbs_mods_count;
	uint32_t mbs_mods_addr;
	uint32_t mbs_syms1;
	uint32_t mbs_syms2;
	uint32_t mbs_syms3;
	uint32_t mbs_syms4;
	uint32_t mbs_mmap_length;
	uint32_t mbs_mmap_addr;
	uint32_t mbs_drives_length;
	uint32_t mbs_drives_addr;
	uint32_t mbs_config_table;
	uint32_t mbs_bootloader_name;
	uint32_t mbs_apm_table;
	uint32_t mbs_vbe_control_info;
	uint32_t mbs_vbe_mode_info;
	uint16_t mbs_vbe_mode;
	uint16_t mbs_interface_seg;
	uint16_t mbs_interface_off;
	uint16_t mbs_interface_len;
} __attribute__((packed));

struct multiboot_module {
	uint32_t start;
	uint32_t end;
	uint32_t string;
	uint32_t reserved;
} __attribute__((packed));

struct multiboot_mmap {
	uint32_t size;
	uint64_t base;
	uint64_t len;
	uint32_t type;
} __attribute__((packed));

struct multiboot_drive {
	uint32_t size;
	uint8_t number;
	uint8_t mode;
	uint16_t cylinders;
	uint8_t heads;
	uint8_t sectors;
	// ports: size - 0x10
} __attribute__((packed));

struct multiboot_apm_table {
	uint16_t version;
	uint16_t cseg;
	uint32_t offset;
	uint16_t cseg_16;
	uint16_t dseg;
	uint16_t flags;
	uint16_t cseg_len;
	uint16_t cseg_16_len;
	uint16_t dseg_len;
} __attribute__((packed));

#endif
