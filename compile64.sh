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

ld -n -o build/kernel.bin \
    -T bootloader/linker.ld \
    build/loader.o \
    build/boot.o \
    build/mode64.o \
    build/kernel.o \
    build/lowlevelio.o \
    build/vga.o \

mkdir build/isofiles
mkdir build/isofiles/boot
mkdir build/isofiles/boot/grub/

cp config/grub.cfg build/isofiles/boot/grub/
cp build/kernel.bin build/isofiles/boot/

grub-mkrescue -o build/os.iso build/isofiles

qemu-system-x86_64 -net none -cdrom build/os.iso