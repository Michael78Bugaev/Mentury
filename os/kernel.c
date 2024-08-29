#include <drv/vga.h>
#include <cpu/memory.h>
#include <cpucall.h>
#include <drv/ps2.h>
#include <task/shell.h>

void kmain()
{
	syscall("Starting dynamic memory...");
	init_dynamic_mem();
	set_codepage_437();
	keyboardInstance();
}