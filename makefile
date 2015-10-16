# Axel Fahy - Rudolf Hohn
# 16.10.2015
#
# Makefile for kernel
#
# 'make'		build ELF file of kernel
# 'make run'	run the operating system on QEMU
# 'make clean'	removes all .o files
# 


.PHONY: run, clean

kernel.iso: kernel.elf
	grub-mkrescue -o $@ .
	
kernel.elf:
	cd kernel && $(MAKE)
	mkdir -p boot/grub
	cp kernel/kernel.elf boot/
	cp grub/grub.cfg boot/grub/

run: kernel.iso
	qemu-system-i386 -hda $<

clean:
	rm -f *.o
	rm -f kernel/*.o
	rm -f kernel/*.elf
	rm -rf boot/
	rm -f kernel.iso


