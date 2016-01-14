# Axel Fahy - Rudolf Hohn
# 13.01.2016
#
# Makefile for user
#
# 'make'		build ELF file of user
# 'make clean'	removes all .o files
#

CC=gcc
CFLAGS=-std=gnu99 -m32 -fno-builtin -ffreestanding -Wall -Wextra $(DEBUG)
ASM=nasm
AFLAGS=-f elf32
LINK=ld -melf_i386 -T app.ld

CMD=shell

.PHONY: clean

shell: shell.o ulib.o syscall.o app_stub.o
	$(LINK) $^ -o $@

ulib.o: ulib.c ulib.h
	$(CC) $(CFLAGS) -c $<

syscall.o: syscall.s syscall.h
	$(ASM) $(AFLAGS) $^

app_stub.o: app_stub.s
	$(ASM) $(AFLAGS) $^


clean:
	rm -f *.o
	rm -f $(CMD)