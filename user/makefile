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
LINK=ld -melf_i386 -Tapp.ld

CMD=shell

.PHONY: clean

all: shell ls cat

shell: shell.o ulib.o syscall.o app_stub.o ../common/string.o
	$(LINK) $^ -o $@

ls: ls.o syscall.o ulib.o app_stub.o ../common/string.o
	$(LINK) $^ -o $@

cat: cat.o syscall.o ulib.o app_stub.o ../common/string.o
	$(LINK) $^ -o $@

ulib.o: ulib.c ulib.h ../common/string.c ../common/string.h syscall.h
	$(CC) $(CFLAGS) -c $< -o $@

shell.o: shell.c ulib.h
	$(CC) $(CFLAGS) -c $< -o $@

ls.o: ls.c ulib.h
	$(CC) $(CFLAGS) -c $< -o $@

cat.o: ls.c ulib.h
	$(CC) $(CFLAGS) -c $< -o $@

../common/string.o: ../common/string.c ../common/string.h
	$(CC) $(CFLAGS) -c $< -o $@

syscall.o: syscall.s syscall.h
	$(ASM) $(AFLAGS) $<

app_stub.o: app_stub.s
	$(ASM) $(AFLAGS) $^


clean:
	rm -f *.o
	rm -f $(CMD)
	rm -f ls
	rm -f cat
