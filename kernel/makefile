

kernel.elf: kernel.o gdt_asm.o
	ld -Tkernel.ld -melf_i386 $< -o $@

kernel.o: kernel.c
	gcc -std=gnu99 -m32 -fno-builtin -ffreestanding -Wall -Wextra -c $< -o $@

gdt_asm.o: gdt_asm.s
	nasm -f elf32 $< -o $@

clean:
	rm -f *.o
