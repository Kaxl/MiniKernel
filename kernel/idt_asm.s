%include "const.inc"

; handler from idt.c
extern exception_handler
extern interruption_handler

section .text   ; start of the text (code) section
align 4         ; the code must be 4 byte aligned

;------------------------------------------------
; CPU exceptions
; Macro for exception with one argument (the exception number)
%macro exception 1
global _exception_%1
_exception_%1:
    cli         ; disable interrupts
    %if %1 < 7 || %1 == 9 || %1 == 14 || %1 == 15 || %1 > 17
        push 0  ; dummy error code in certain case
    %endif
    push %1     ; exception number
    jmp exception_wrapper
%endmacro
; Creation of all exception (0 to 20)
%assign i 0
%rep 20
exception i
%assign i i+1
%endrep

;------------------------------------------------
; IRQ
; Macro for irq with one argument (the irq number)
%macro irq 1
global _irq_%1
_irq_%1:
    cli          ; disable interrupts
    push    0    ; dummy error code
    push    %1   ; irq number
    jmp     interruptions_wrapper
%endmacro
; Creation of all irq (0 to 15)
%assign i 0
%rep 15
irq i
%assign i i+1
%endrep

;------------------------------------------------
; Wrapper for exceptions

exception_wrapper :
    ; Save all registers
    push    eax
    push    ebx
    push    ecx
    push    edx
    push    esi
    push    edi
    push    ebp
    push    ds
    push    es
    push    fs
    push    gs

    ; Load kernel data descriptor into all segments
    mov     ax,GDT_KERNEL_DATA_SELECTOR
    mov     ds,ax
    mov     es,ax
    mov     fs,ax
    mov     gs,ax

    ; Pass the stack pointer (which gives the CPU context) to the C function
    mov     eax,esp
    push    eax
    call    exception_handler  ; implemented in idt.c
    pop     eax  ; only here to balance the "push eax" done before the call

    ; Restore all registers
    pop     gs
    pop     fs
    pop     es
    pop     ds
    pop     ebp
    pop     edi
    pop     esi
    pop     edx
    pop     ecx
    pop     ebx
    pop     eax
    
	; Fix the stack pointer due to the 2 push done before the call to exception_wrapper
    add     esp,8
    iret

;------------------------------------------------
; Wrapper for interruptions

interruptions_wrapper:
    ; Save all registers
    push    eax
    push    ebx
    push    ecx
    push    edx
    push    esi
    push    edi
    push    ebp
    push    ds
    push    es
    push    fs
    push    gs

    ; Load kernel data descriptor into all segments
    mov     ax,GDT_KERNEL_DATA_SELECTOR
    mov     ds,ax
    mov     es,ax
    mov     fs,ax
    mov     gs,ax

    ; Pass the stack pointer (which gives the CPU context) to the C function
    mov     eax,esp
    push    eax
    call    interruption_handler  ; implemented in idt.c
    pop     eax  ; only here to balance the "push eax" done before the call

    ; Restore all registers
    pop     gs
    pop     fs
    pop     es
    pop     ds
    pop     ebp
    pop     edi
    pop     esi
    pop     edx
    pop     ecx
    pop     ebx
    pop     eax
    
	; Fix the stack pointer due to the 2 push done before the call to exception_wrapper
    add     esp,8
    iret

