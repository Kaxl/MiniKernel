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

kernel.elf: kernel.o gdt_asm.o
	ld -Tkernel.ld -melf_i386 $< -o $@

kernel.o: kernel.c gdt.o
	$(CC) $(CFLAGS) -c $< -o $@

gdt.o: base.o gdt.c
	$(CC) $(CFLAGS) -c $< -o $@

gdt_asm.o: gdt_asm.s
	nasm -f elf32 $< -o $@

base.o: ../common/base.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o
	rm -f *.elf
