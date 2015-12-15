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
X=10240		# Block size
Y=1000			# Number of file entries
Z=1000			# Number of data blocks available
FT1=fileA
FT2=fileB
FT3=fileC
FT4=lorem
<<<<<<< HEAD
FT5=fileST
=======
FT_SPLASH=splash_screen
>>>>>>> 1857e7a03cdce2a28005949466cde09e19f61be5

.PHONY: run, clean

$(KERNEL): kernel.elf
	grub-mkrescue -d /usr/lib/grub/i386-pc -o $@ .

kernel.elf:
	$(MAKE) -C kernel DEBUG=$(MODE)
	mkdir -p boot/grub
	cp kernel/kernel.elf boot/
	cp grub/grub.cfg boot/grub/

$(FS):
	$(MAKE) -C tools
	cd tools && ./pfscreate $(FS) $(X) $(Y) $(Z)
	cd tools && ./pfsadd $(FS) $(FT1)
	cd tools && ./pfsadd $(FS) $(FT2)
	cd tools && ./pfsadd $(FS) $(FT3)
	cd tools && ./pfsadd $(FS) $(FT4)
<<<<<<< HEAD
	cd tools && ./pfsadd $(FS) $(FT5)
=======
	cd tools && ./pfsadd $(FS) $(FT_SPLASH)
>>>>>>> 1857e7a03cdce2a28005949466cde09e19f61be5
	cp tools/$(FS) ./

run: $(KERNEL) $(FS)
	qemu-system-i386 -cdrom $(KERNEL) -hda $(FS)

clean:
	rm -f *.o
	rm -rf boot/
	rm -f $(KERNEL)
	rm -f $(FS)
	$(MAKE) -C kernel clean
	$(MAKE) -C kernel clean

