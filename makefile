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

MAKE=make
KERNEL=kernel.iso
FS=fs.img
X=1024			# Block size
Y=100			# Number of file entries
Z=1000			# Number of data blocks available
FT_SPLASH=splash_screen

.PHONY: run, clean

$(KERNEL): kernel.elf $(FS)
	grub-mkrescue -d /usr/lib/grub/i386-pc -o $@ .

kernel.elf:
	$(MAKE) -C kernel DEBUG=$(MODE)
	mkdir -p boot/grub
	cp kernel/kernel.elf boot/
	cp grub/grub.cfg boot/grub/

$(FS):
	$(MAKE) -C tools
	$(MAKE) -C user
	cp user/shell tools/shell
	cp user/ls tools/ls
	cp user/cat tools/cat
	cd tools && ./pfscreate $(FS) $(X) $(Y) $(Z)
	cd tools && ./pfsadd $(FS) $(FT_SPLASH)
	cd tools && ./pfsadd $(FS) shell
	cd tools && ./pfsadd $(FS) ls
	cd tools && ./pfsadd $(FS) cat
	cp tools/$(FS) ./

run: $(KERNEL)
	qemu-system-i386 -monitor stdio -cdrom $(KERNEL) -hda $(FS)

clean:
	rm -f *.o
	rm -rf boot/
	rm -f common/*.o
	rm -f $(KERNEL)
	rm -f $(FS)
	rm -f shell
	rm -f ls
	rm -f cat
	$(MAKE) -C kernel clean
	$(MAKE) -C tools clean
	$(MAKE) -C user clean

