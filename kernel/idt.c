#include "idt.h"
#include "x86.h"

// Declaration of IDT
static idt_entry_t idt[256];

// Pointer on the IDT
static idt_ptr_t idt_ptr;

// CPU context used when saving/restoring context from an interrupt
typedef struct regs_st {
    uint32_t gs, fs, es, ds;
    uint32_t ebp, edi, esi;
    uint32_t edx, ecx, ebx, eax;
    uint32_t number, error_code;
    uint32_t eip, cs, eflags, esp, ss;
} regs_t;

// Build and return an IDT entry.
// selector is the code segment selector in which resides the ISR (Interrupt Service Routine)
// offset is the address of the ISR (NOTE: for task gates, offset must be 0)
// type indicates the IDT entry type
// dpl is the privilege level required to call the associated ISR
static idt_entry_t idt_build_entry(uint16_t selector, uint32_t offset, uint8_t type, uint8_t dpl) {
	idt_entry_t entry;
    entry.offset15_0 = offset & 0xffff;
    entry.selector = selector;
    entry.reserved = 0;
    entry.type = type;
    entry.dpl = dpl;
    entry.p = 1;
    entry.offset31_16 = (offset >> 16) & 0xffff;
	return entry;
}

// Exception handler
void exception_handler(regs_t *regs) {
    /* TODO : switch sur regs, printf de la bonne exception */

}

// Interruption handler
void interruption_handler(regs_t *regs) {
    /* TODO : switch sur regs, printf de la bonne exception */

}

void idt_init() {

    // Set limit of idt_ptr and point it on the IDT
    //idt_ptr.limit = sizeof(idt) - 1;     // Limit is the size of IDT - 1
    idt_ptr.limit = 0xFFFF;     // Limit is the size of IDT - 1

    // Creation of entries in IDT
    // Processor exception
    idt[0] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR, (uint32_t)&_exception_1, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[1] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR, 0, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[2] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR, 0, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[3] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR, 0, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[4] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR, 0, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[5] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR, 0, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[6] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR, 0, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[7] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR, 0, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[8] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR, 0, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[9] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR, 0, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[10] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR, 0, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[11] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR, 0, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[12] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR, 0, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[13] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR, 0, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[14] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR, 0, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[15] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR, 0, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[16] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR, 0, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[17] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR, 0, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[18] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR, 0, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[19] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR, 0, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[20] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR, 0, TYPE_INTERRUPT_GATE, DPL_KERNEL);

    // IRQ : Interrupt request

    idt_ptr.base = (uint32_t)idt; // Base of idt is the first element of idt

    // Load the IDT

    //LIDT [EAX] ou eax contient l'address de la struture idtr


}

