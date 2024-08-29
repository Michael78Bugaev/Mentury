#include <cpucall.h>
#include <stdint.h>
#include <cpu/io.h>
#include <drv/vga.h>

void syscall(u8 *msg)
{
    kprint_colored("[Mentury syscall]: ", 0x0B);
    kprint_colored(msg, 0x0F);
}