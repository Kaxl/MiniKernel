/*
 * =====================================================================================
 *
 *       Filename:  controller_asm.s
 *
 *    Description:  Function to access peripherals and communicate with them
 *                  AL is 8-bit register
 *                  AX is 16-bit register
 *                  EAX is 32-bit register
 *
 *        Version:  1.0
 *        Created:  10/16/2015 11:20:41 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Axel Fahy, Rudolf Hohn
 *   Organization:  HES-SO hepia section ITI
 *
 * =====================================================================================
 */

global outb
global outw
global inb
global inw

section .txt

; void outb(uint16_t port, uint8_t data)
outb:
    ; Start of function, save the stack
    push    ebp
    mov     ebp, esp
    
    ; Get arguments
    mov     al,[ebp+8]      ; Port
    mov     dl,[ebp+12]     ; Data
    
    ; Write the Data on the Port
    out     al, dl

    ; End of function, restore the stack
    mov     esp,ebp
    pop     ebp
    ret

; void outw(uint16_t port, uint16_t data)
outw:
    push    ebp
    mov     ebp, esp

    mov     ax,[ebp+8]
    mov     dx,[ebp+12]
    
    out     ax,dx

    mov     esp,ebp
    pop     ebp
    ret

; uint8_t inb(uint16_t port)
inb:
    ; Start of function, save the stack
    push    ebp
    mov     ebp, esp

    ; Get argument
    mov     al,[ebp+8]      ; Port
    
    ; Read the data on the Port
    in      dl, al
    ; Return the data (on the top of the stack)
    push    dl

    ; End of function, restore the stack
    mov     esp,ebp
    pop     ebp
    ret

; uint16_t inw(uint16_t port)
inw:
    push    ebp
    mov     ebp, esp

    mov     ax,[ebp+8]
    
    in      dx,ax
    push    dx

    mov     esp,ebp
    pop     ebp
    ret
