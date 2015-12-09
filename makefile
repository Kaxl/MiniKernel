# Axel Fahy - Rudolf Hohn
# 16.10.2015
#
# Makefile for kernel
#
# 'make'		build ELF file of kernel
# 'make run'	run the operating system on QEMU
# 'make clean'	removes all .o files
#

KERNEL=kernel.iso
FS=fs.img

.PHONY: run, clean

kernel.iso: kernel.elf
	grub-mkrescue -d /usr/lib/grub/i386-pc -o $@ .

kernel.elf:
	cd kernel && $(MAKE)
	mkdir -p boot/grub
	cp kernel/kernel.elf boot/
	cp grub/grub.cfg boot/grub/

run: $(KERNEL) $(FS)
	qemu-system-i386 -cdrom $(KERNEL)
	qemu-system-i386 -hda $(FS)

clean:
	rm -f *.o
	rm -rf boot/
	rm -f kernel.iso
	cd kernel && $(MAKE) clean


