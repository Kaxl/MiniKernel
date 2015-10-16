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

STACK_SIZE  equ 0x3e800     ; Size of stack in hex

entrypoint:
	; Bootloader code starts executing here
	cli  ; disable hardware interrupts

    ; Init of stack pointer and base pointer
    mov     esp,STACK_SIZE ; Init at end of stack 
    mov     ebp,STACK_SIZE ; Init at end of stack 
	; TODO : initialiser le pointeur de pile ainsi qu'EBP (à la même valeur)
    ; Rappel : la pile "grandi" en descendant !
	; ...


    ; Main function
    ; TODO
    mov     eax,0xB8000
    mov     word [eax], 0x0E01

	; TODO : appeler la fonction principale du kernel (code C)
	; Celle-ci doit etre visible par le linker
	; ...

	; infinite loop (should never get here)
.forever:
	hlt
	jmp .forever

;---------------------------------------------------------------------------------------------------
; stack section
section .stack
    align   4               ; Alignment on 4 bytes
    ;size: resb  STACK_SIZE  ; Reserve 256KB
    resb    STACK_SIZE      ; Reserve 256KB
    

; TODO : ajouter une section pour la pile kernel dans laquelle
; reserver au moins 256KB grace a la directive "resb".
; Cette section devra etre alignee sur 4 bytes.
; ...
