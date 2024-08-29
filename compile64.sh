#!/bin/bash

rm -r -f build
mkdir build

nasm -f elf64 bootloader/loader.asm -o build/loader.o
nasm -f elf64 bootloader/boot.asm -o build/boot.o
nasm -f elf64 bootloader/long_mode_start.asm -o build/mode64.o

gcc -m64 -c os/kernel.c -I ./include -o build/kernel.o
# g++ -m64 -c os/tools.h -o build/tools_h.o
gcc -m64 -c os/cpu/lowlevelio.c -I ./include -o build/lowlevelio.o
gcc -m64 -c os/drivers/vga.c -I ./include -o build/vga.o
gcc -m64 -c os/cpu/cpucall.c  -I ./include -o build/cpucall.o
gcc -m64 -c os/cpu/string.c -I ./include -o build/string.o
gcc -m64 -c os/general/shell.c -I ./include -o build/shell.o
gcc -m64 -c os/drivers/keyboard.c -I ./include -o build/kb.o --std=c2x
gcc -m64 -c os/general/cmos.c -I ./include -o build/cmos.o
gcc -m64 -c os/cpu/memory.c -I ./include -o build/memory.o

# gcc -m64 -c os/cpu/idt.c -I ./include -o build/idt.o

# -fstack-protector -z muldefs

ld -n -o build/kernel.bin \
    -T bootloader/linker.ld \
    build/loader.o \
    build/boot.o \
    build/mode64.o \
    build/kernel.o \
    build/cmos.o \
    build/lowlevelio.o \
    build/cpucall.o \
    build/vga.o \
    build/shell.o \
    build/string.o \
    build/kb.o \
    build/memory.o \

mkdir -p build/isofiles/boot/grub/

cp config/grub.cfg build/isofiles/boot/grub/
cp build/kernel.bin build/isofiles/boot/

grub-mkrescue -o build/os.iso build/isofiles

qemu-system-x86_64 -net none -cdrom build/os.iso