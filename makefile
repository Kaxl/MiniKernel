# Axel Fahy - Rudolf Hohn
# 16.10.2015
#
# Makefile for kernel
#
# 'make'					build ELF file of kernel
# 'make run'				run the operating system on QEMU
# 'make clean'				removes all .o files
# 'make MODE=-DTEST run 	make in DEBUG mode
#

KERNEL=kernel.iso
FS=fs.img
X=1024		# Block size
Y=100		# Number of file entries
Z=512		# Number of data blocks available
FT1=fileA
FT2=fileB
FT3=fileC
FT4=lorem

.PHONY: run, clean

$(KERNEL): kernel.elf
	grub-mkrescue -d /usr/lib/grub/i386-pc -o $@ .

kernel.elf:
	cd kernel && $(MAKE) DEBUG=$(MODE)
	mkdir -p boot/grub
	cp kernel/kernel.elf boot/
	cp grub/grub.cfg boot/grub/

$(FS):
	cd tools && $(MAKE)
	cd tools && ./pfscreate $(FS) $(X) $(Y) $(Z)
	cd tools && ./pfsadd $(FS) $(FT1)
	cd tools && ./pfsadd $(FS) $(FT2)
	cd tools && ./pfsadd $(FS) $(FT3)
	cd tools && ./pfsadd $(FS) $(FT4)
	cp tools/$(FS) ./

run: $(KERNEL) $(FS)
	qemu-system-i386 -cdrom $(KERNEL) -hda $(FS)

clean:
	rm -f *.o
	rm -rf boot/
	rm -f $(KERNEL)
	rm -f $(FS)
	cd kernel && $(MAKE) clean
	cd tools && $(MAKE) clean

