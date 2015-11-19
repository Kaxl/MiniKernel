# Axel Fahy - Rudolf Hohn
# 16.10.2015
#
# Makefile for kernel
#
# 'make'		build ELF file of kernel
# 'make clean'	removes all .o files
#

CC=gcc
CFLAGS=-std=gnu99 -m32 -fno-builtin -ffreestanding -Wall -Wextra $(DEBUG)

.PHONY: clean

kernel.elf: kernel.o gdt.o idt.o bootloader.o base.o pic.o gdt_asm.o idt_asm.o screen.o controller_asm.o string.o ../test/test_cases.o
	ld -melf_i386 -T kernel.ld $^ -o $@

kernel.o: kernel.c kernel.h
	$(CC) $(CFLAGS) -c $<

bootloader.o: bootloader.s
	nasm -f elf32 $^

gdt.o: gdt.c gdt.h
	$(CC) $(CFLAGS) -c $<

pic.o: pic.c pic.h
	$(CC) $(CFLAGS) -c $<

gdt_asm.o: gdt_asm.s 
	nasm -f elf32 $^

idt.o: idt.c idt.h
	$(CC) $(CFLAGS) -c $<

idt_asm.o: idt_asm.s 
	nasm -f elf32 $^

base.o: base.c base.h
	$(CC) $(CFLAGS) -c $< -o $@
	
screen.o: screen.c screen.h
	$(CC) $(CFLAGS) -c $< -o $@

controller_asm.o: controller_asm.s controller.h
	nasm -f elf32 $<

string.o: string.c string.h
	$(CC) $(CFLAGS) -c $< -o $@

../test/test_cases.o: ../test/test_cases.c ../test/test_cases.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o
	rm -f *.elf
	rm -f ../test/*.o
