# Axel Fahy - Rudolf Hohn
# 16.10.2015
#
# Makefile for kernel
#
# 'make'		build ELF file of kernel
# 'make clean'	removes all .o files
#

CC=gcc
#CFLAGS=-std=gnu99 -m32 -fno-builtin -ffreestanding -Wall -Wextra
CFLAGS=-std=gnu99 -m32 -fno-builtin -ffreestanding -Wall -Wextra -DTEST

.PHONY: clean

kernel.elf: kernel.o gdt.o bootloader.o ../common/base.o gdt_asm.o ../common/screen.o ../common/controller_asm.o test_cases.o
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
	
../common/screen.o: ../common/screen.c
	$(CC) $(CFLAGS) -c $^ -o $@

../common/controller_asm.o: ../common/controller_asm.s
	nasm -f elf32 $^

test_cases.o: test_cases.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f ../common/*.o
	rm -f *.o
	rm -f *.elf
