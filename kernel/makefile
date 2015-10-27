# Axel Fahy - Rudolf Hohn
# 16.10.2015
#
# Makefile for kernel
#
# 'make'		build ELF file of kernel
# 'make clean'	removes all .o files
#

CC=gcc
CFLAGS=-std=gnu99 -m32 -fno-builtin -ffreestanding -Wall -Wextra 

.PHONY: clean

kernel.elf: kernel.o gdt.o bootloader.o ../common/base.o gdt_asm.o
	ld -melf_i386 -T kernel.ld $^ -o $@

kernel.o: kernel.c
	$(CC) $(CFLAGS) -c $^

bootloader.o: bootloader.s
	nasm -f elf32 $^

gdt.o: gdt.c
	$(CC) $(CFLAGS) -c $^

gdt_asm.o: gdt_asm.s
	nasm -f elf32 $^

../common/base.o: ../common/base.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f *.o
	rm -f *.elf
