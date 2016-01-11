#define GDT_INDEX_TO_SELECTOR(idx) ((idx) << 3)

// Return a TSS entry  specified by the TSS structure and privilege level passed in arguments.
// NOTE: a TSS entry can only reside in the GDT!
gdt_entry_t gdt_make_tss(tss_t *tss, uint8_t dpl) {
	return build_entry((uint32_t)tss, sizeof(tss_t)-1, TYPE_TSS, S_SYSTEM, DB_SYS, 0, dpl);
}

// Can only be set in the GDT!
gdt_entry_t gdt_make_ldt(uint32_t base, uint32_t limit, uint8_t dpl) {
	return build_entry(base, limit, TYPE_LDT, S_SYSTEM, DB_SYS, 0, dpl);
}

uint gdt_entry_to_selector(gdt_entry_t *entry) {
	return GDT_INDEX_TO_SELECTOR(entry - gdt);
}

void setup_task() {
	// gdt[4] : Task1 TSS descriptor
	// gdt[5] : Task1 LDT descriptor

	static tss_t task_tss;
	static gdt_entry_t task_ldt[2];

	// Add the task's TSS and LDT to the GDT
	gdt[4] = gdt_make_tss(&task_tss, DPL_KERNEL);
	gdt[5] = gdt_make_ldt((uint32_t)task_ldt, sizeof(task_ldt)-1, DPL_KERNEL);
	int gdt_tss_sel = gdt_entry_to_selector(&gdt[4]);
	int gdt_ldt_sel = gdt_entry_to_selector(&gdt[5]);

	// Define code and data segments in the LDT; both segments are overlapping
	uint32_t task_addr = 0x800000;  // @8MB
	int ldt_code_idx = 0;
	int ldt_data_idx = 1;
	uint limit = 0x10000;  // limit of 64KB
	task_ldt[ldt_code_idx] = gdt_make_code_segment(task_addr, limit / 4096, DPL_USER);  // code
	task_ldt[ldt_data_idx] = gdt_make_data_segment(task_addr, limit / 4096, DPL_USER);  // data + stack

	// Initialize the TSS fields
	// The LDT selector must point to the task's LDT
	task_tss.ldt_selector = gdt_ldt_sel;

	// Setup code and stack pointers
	task_tss.eip = 0;
	task_tss.esp = task_tss.ebp = limit;  // stack pointers

	// Code and data segment selectors are in the LDT
	task_tss.cs = GDT_INDEX_TO_SELECTOR(ldt_code_idx) | DPL_USER | LDT_SELECTOR;
	task_tss.ds = task_tss.es = task_tss.fs = task_tss.gs = task_tss.ss = GDT_INDEX_TO_SELECTOR(ldt_data_idx) | DPL_USER | LDT_SELECTOR;
	task_tss.eflags = 512;  // Activate hardware interrupts (bit 9)

	// Task's kernel stack
	static uchar task_kernel_stack[8192];
	task_tss.ss0 = GDT_KERNEL_DATA_SELECTOR;
	task_tss.esp0 = (uint32_t)(task_kernel_stack) + sizeof(task_kernel_stack);
}

// Initialize the GDT
void gdt_init() {
	// Initialization of the GDT pointer
	// ...

	// Entries for null segment, kernel code and kernel data segments
	// ...

	// Load the GDT
	// ...

	// gdt[3] : entry for initial kernel TSS (CPU state of first task saved there)
	static uint8_t initial_tss_kernel_stack[65536];  // 64KB of stack
	static tss_t initial_tss;
	gdt[3] = gdt_make_tss(&initial_tss, DPL_KERNEL);
	memset(&initial_tss, 0, sizeof(tss_t));
	initial_tss.ss0 = GDT_KERNEL_DATA_SELECTOR;
	initial_tss.esp0 = ((uint32_t)initial_tss_kernel_stack) + sizeof(initial_tss_kernel_stack);

	// Load the task register to point to the initial TSS selector.
	// IMPORTANT: The GDT must be already loaded before loading the task register!
	extern void load_task_register(uint16_t tss_selector);  // Implemented in task_asm.s
	load_task_register(gdt_entry_to_selector(&gdt[3]));

	// Setup a task
	task_setup();	
}

