#include "multiboot.h"

void fix_multiboot_info(struct multiboot_info *mbinfo) {
	// fix pointers in multiboot_info struct. since the kernel is mapped
	// to 3GB, all pointers have to be offset by KERNEL_BASE

	mbinfo->mbs_mods_addr += KERNEL_BASE;
	mbinfo->mbs_mmap_addr += KERNEL_BASE;
	mbinfo->mbs_drives_addr += KERNEL_BASE;

	// each module might need an update as well?
}
