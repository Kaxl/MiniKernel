extern runKernel
global entrypoint  ; the entry point symbol defined in kernel.ld

; Values for the multiboot header
MULTIBOOT_HEADER_MAGIC     equ 0x1BADB002
MULTIBOOT_HEADER_FLAGS     equ 0x0
; magic + checksum + flags must equal 0
MULTIBOOT_HEADER_CHECKSUM  equ -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

;---------------------------------------------------------------------------------------------------
; bootloader section
; This section must be located at the very beginning of the kernel image.

section .bootloader
align 4    ; section aligned to a 4 bytes boundary


; Minimum multiboot header
dd MULTIBOOT_HEADER_MAGIC
dd MULTIBOOT_HEADER_FLAGS
dd MULTIBOOT_HEADER_CHECKSUM

STACK_SIZE  equ 0x40000     ; Size of stack in hex (256KB)

entrypoint:
	; Bootloader code starts executing here
	cli  ; disable hardware interrupts

    ; Init of stack pointer and base pointer
    mov     esp, stack      ; Init at end of stack 
    mov     ebp, stack      ; Init at end of stack 


    ; Main function
    call runKernel 

	; infinite loop (should never get here)
.forever:
	hlt
    jmp .forever

;---------------------------------------------------------------------------------------------------
; stack section
section .stack
    align   4                   ; Alignment on 4 bytes
    stack:  resb  STACK_SIZE    ; Reserve 256KB (not initialized)
    
