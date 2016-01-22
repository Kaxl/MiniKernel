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
ASM=nasm
AFLAGS=-f elf32

.PHONY: clean

kernel.elf: kernel.o gdt.o idt.o keyboard.o timer.o bootloader.o base.o ide.o pic.o gdt_asm.o idt_asm.o screen.o task_asm.o syscall.o syscall_asm.o controller_asm.o ../common/string.o ../common/pfs.o
	ld -melf_i386 -Tkernel.ld $^ -o $@

kernel.o: kernel.c kernel.h x86.h gdt.h idt.h pic.h screen.h keyboard.h timer.h ../common/pfs.h
	$(CC) $(CFLAGS) -c $<

bootloader.o: bootloader.s
	$(ASM) $(AFLAGS) $^

gdt.o: gdt.c gdt.h ../common/types.h base.h task.h ../common/pfs.h x86.h
	$(CC) $(CFLAGS) -c $<

pic.o: pic.c pic.h controller.h
	$(CC) $(CFLAGS) -c $<

keyboard.o: keyboard.c keyboard.h screen.h colors.h ../common/types.h controller.h
	$(CC) $(CFLAGS) -c $<

timer.o: timer.c timer.h controller.h ../common/types.h
	$(CC) $(CFLAGS) -c $<

gdt_asm.o: gdt_asm.s
	$(ASM) $(AFLAGS) $^

idt.o: idt.c idt.h x86.h screen.h colors.h pic.h keyboard.h timer.h base.h ../common/types.h
	$(CC) $(CFLAGS) -c $<

ide.o: ide.c ide.h controller.h ../common/types.h
	$(CC) $(CFLAGS) -c $<

idt_asm.o: idt_asm.s
	$(ASM) $(AFLAGS) $^

base.o: base.c base.h
	$(CC) $(CFLAGS) -c $< -o $@

screen.o: screen.c screen.h base.h colors.h controller.h ../common/string.h
	$(CC) $(CFLAGS) -c $< -o $@

controller_asm.o: controller_asm.s controller.h
	$(ASM) $(AFLAGS) $<

syscall_asm.o: syscall_asm.s
	$(ASM) $(AFLAGS) $<

task_asm.o: task_asm.s task.h
	$(ASM) $(AFLAGS) $<

syscall.o: syscall.c ../common/syscall_nb.h ../common/types.h ../common/pfs.h gdt.h screen.h keyboard.h timer.h
	$(CC) $(CFLAGS) -c $< -o $@

../common/string.o: ../common/string.c ../common/string.h
	$(CC) $(CFLAGS) -c $< -o $@

../common/pfs.o: ../common/pfs.c ../common/pfs.h ../common/types.h base.h ide.h ../common/string.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o
	rm -f *.elf
