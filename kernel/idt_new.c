void idt_init() {
	// IDT initialization
	// ...

	// IDT entry 48 used for system calls
	extern void _syscall_handler();  // Implemented in syscall_asm.s
	idt[48] = idt_build_entry(code_sel, (uint32_t)&_syscall_handler, TYPE_TRAP_GATE, DPL_USER);

	// Load the IDT
	...
}

