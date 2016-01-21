#include "../common/types.h"
#include "base.h"
#include "gdt.h"
#include "x86.h"
#include "task.h"
#include "../common/pfs.h"
#include "screen.h"

extern void call_task(uint16_t tss_selector);

// Declaration of GDT
// There are two entries by task
static gdt_entry_t gdt[FIRST_TASK_ENTRY + NB_TASKS_MAX * 2];

// Pointer on the GDT
static gdt_ptr_t gdt_ptr;

// Declaration of tasks
static task_t tasks[NB_TASKS_MAX];

// Build and return a GDT entry given the various arguments (see Intel manuals).
static gdt_entry_t build_entry(uint32_t base, uint32_t limit, uint8_t type, uint8_t s, uint8_t db, uint8_t granularity, uint8_t dpl) {
	gdt_entry_t entry;
    // For a TSS and LDT, base is the addresse of the TSS/LDT structure
    // and limit is the size of the structure.
    entry.lim15_0 = limit & 0xffff;
    entry.base15_0 = base & 0xffff;
    entry.base23_16 = (base >> 16) & 0xff;
    entry.type = type;  // See TYPE_xxx flags
    entry.s = s;        // 1 for segments; 0 for system (TSS, LDT, gates)
    entry.dpl = dpl;    // privilege level
    entry.present = 1;  // present in memory
    entry.lim19_16 = (limit >> 16) & 0xf;
    entry.avl = 0;      // available for use
    entry.l = 0;        // should be 0 (64-bit code segment)
    entry.db = db;      // 1 for 32-bit code and data segments; 0 for system (TSS, LDT, gate)
    entry.granularity = granularity;  // granularity of the limit value: 0 = 1 byte; 1 = 4096 bytes
    entry.base31_24 = (base >> 24) & 0xff;
	return entry;
}

// Return a NULL entry.
static gdt_entry_t gdt_make_null_segment() {
	gdt_entry_t entry;
    memset(&entry, 0, sizeof(gdt_entry_t));
	return entry;
}

// Return a code segment specified by the base, limit and privilege level passed in arguments.
static gdt_entry_t gdt_make_code_segment(uint32_t base, uint32_t limit, uint8_t dpl) {
    return build_entry(base, limit, TYPE_CODE_EXECREAD, S_CODE_OR_DATA, DB_SEG, 1, dpl);
}

// Return a data segment specified by the base, limit and privilege level passed in arguments.
static gdt_entry_t gdt_make_data_segment(uint32_t base, uint32_t limit, uint8_t dpl) {
    return build_entry(base, limit, TYPE_DATA_READWRITE, S_CODE_OR_DATA, DB_SEG, 1, dpl);
}

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

/**
 * @brief Change the context of a task
 *
 * @param id Init of the task
 */
void setup_task(int id) {
    tasks[id].free = false;
	// Setup code and stack pointers
	tasks[id].tss.eip = 0;
	tasks[id].tss.esp = tasks[id].tss.ebp = tasks[id].limit;  // stack pointers
}

/**
 * @brief Initialization of a task
 *
 * @param id ID of the task
 */
void init_task(int id) {
	memset(&tasks[id].tss, 0, sizeof(tss_t));

	// Add the task's TSS and LDT to the GDT
	gdt[FIRST_TASK_ENTRY + id * 2] = gdt_make_tss(&tasks[id].tss, DPL_KERNEL);
	gdt[FIRST_TASK_ENTRY + id * 2 + 1] = gdt_make_ldt((uint32_t)tasks[id].ldt, sizeof(tasks[id].ldt)-1, DPL_KERNEL);

    tasks[id].tss_sel = gdt_entry_to_selector(&gdt[FIRST_TASK_ENTRY + id * 2]);
    tasks[id].ldt_sel = gdt_entry_to_selector(&gdt[FIRST_TASK_ENTRY + id * 2 + 1]);

	// Define code and data segments in the LDT; both segments are overlapping
	tasks[id].limit = LIMIT_SIZE;  // limit of 1M
    tasks[id].addr = (uint32_t)(FIRST_TASK_ADDR + id * tasks[id].limit);  // @8MB

	int ldt_code_idx = 0;
	int ldt_data_idx = 1;
	tasks[id].ldt[ldt_code_idx] = gdt_make_code_segment(tasks[id].addr, tasks[id].limit / 4096, DPL_USER);  // code
	tasks[id].ldt[ldt_data_idx] = gdt_make_data_segment(tasks[id].addr, tasks[id].limit / 4096, DPL_USER);  // data + stack

	// Initialize the TSS fields
	// The LDT selector must point to the task's LDT
	tasks[id].tss.ldt_selector = tasks[id].ldt_sel;

	// Code and data segment selectors are in the LDT
	tasks[id].tss.cs = GDT_INDEX_TO_SELECTOR(ldt_code_idx) | DPL_USER | LDT_SELECTOR;
	tasks[id].tss.ds = tasks[id].tss.es = tasks[id].tss.fs = tasks[id].tss.gs = tasks[id].tss.ss = GDT_INDEX_TO_SELECTOR(ldt_data_idx) | DPL_USER | LDT_SELECTOR;
	tasks[id].tss.eflags = 512;  // Activate hardware interrupts (bit 9)

	// Task's kernel stack
	tasks[id].tss.ss0 = GDT_KERNEL_DATA_SELECTOR;
	tasks[id].tss.esp0 = (uint32_t)(tasks[id].kernel_stack) + sizeof(tasks[id].kernel_stack);

    setup_task(id);

    tasks[id].free = true;
}

void mytask() {
    //asm volatile("int $0x3");
    //int a = 2 / 0;
    int* p = (int *)0x10000;
    *p = 0x1234;
    while(1);
}

int exec_task(char* filename) {
    // Find a free task
    int idTask = 0;
    while (idTask <= NB_TASKS_MAX && !tasks[idTask].free)
        idTask++;

    // If there is no task free available, return an error
    if (idTask >= NB_TASKS_MAX)
        return -1;

    // Copy of program memory into the task address
    if (file_read(filename, (void*)tasks[idTask].addr) < 0)
        return -1;

    setup_task(idTask);
    call_task((uint16_t)tasks[idTask].tss_sel);

    // After the task, set it as free
    tasks[idTask].free = true;
    return 1;
}

// Initialize the GDT
void gdt_init() {
	// Initialization of the GDT pointer
    // Set limit of gdt_ptr and point it on the GDT
    gdt_ptr.limit = sizeof(gdt) - 1;

    // Creation of segments (code and data segments) in a "FLAT" mode
    // Code and data segments have access to the same memory (DPL = 0)
    gdt[0] = gdt_make_null_segment();
    gdt[1] = gdt_make_code_segment(0, 0xFFFFF, 0);
    gdt[2] = gdt_make_data_segment(0, 0xFFFFF, 0);

    gdt_ptr.base = (uint32_t)gdt; // Base of gdt is the first segment

    // Load the GDT
    gdt_flush(&gdt_ptr);

	// gdt[3] : entry for initial kernel TSS (CPU state of first task saved there)
	static uint8_t initial_tss_kernel_stack[KERNEL_STACK_SIZE];  // 64KB of stack
	static tss_t initial_tss;

	gdt[3] = gdt_make_tss(&initial_tss, DPL_KERNEL);

	memset(&initial_tss, 0, sizeof(tss_t));
	initial_tss.ss0 = GDT_KERNEL_DATA_SELECTOR;
	initial_tss.esp0 = ((uint32_t)initial_tss_kernel_stack) + sizeof(initial_tss_kernel_stack);

	// Load the task register to point to the initial TSS selector.
	// IMPORTANT: The GDT must be already loaded before loading the task register!
	extern void load_task_register(uint16_t tss_selector);  // Implemented in task_asm.s
	load_task_register(gdt_entry_to_selector(&gdt[3]));

	// Init all tasks
    for (int i = 0; i < NB_TASKS_MAX; i++) {
	    init_task(i);
    }
}
