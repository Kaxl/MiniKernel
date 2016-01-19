#ifndef _GDT_H_
#define _GDT_H_

#include "../common/types.h"
#include "task.h"

#define LDT_SIZE            2
#define KERNEL_STACK_SIZE   65536
#define NB_TASKS_MAX        8
#define FIRST_TASK_ENTRY    4           // Same index as the example
#define LIMIT_SIZE          0x100000    // Limit size of 1M

// Structure of a GDT descriptor. There are 2 types of descriptors: segments and TSS.
// Section 3.4.5 of Intel 64 & IA32 architectures software developer's manual describes
// segment descriptors while section 6.2.2 describes TSS descriptors.
typedef struct gdt_entry_st {
    uint16_t lim15_0;
    uint16_t base15_0;
    uint8_t base23_16;

    uint8_t type : 4;
    uint8_t s : 1;
    uint8_t dpl : 2;
    uint8_t present : 1;

    uint8_t lim19_16 : 4;
    uint8_t avl : 1;
    uint8_t l : 1;
    uint8_t db : 1;
    uint8_t granularity : 1;

    uint8_t base31_24;
} __attribute__((packed)) gdt_entry_t;

/**
 * @brief Task structure
 *
 * Store tss and ldt used by a task
 */
typedef struct task_t {
	tss_t tss;
    int ldt_sel;
    int tss_sel;
	gdt_entry_t ldt[LDT_SIZE];
	uchar kernel_stack[KERNEL_STACK_SIZE];
    uint32_t addr;                          // Global address of task
    uint limit;                             // Limit of the task
    bool free;                              // Boolean to indicate if the task is free
} __attribute__((packed)) task_t;

// Structure describing a pointer to the GDT descriptor table.
// This format is required by the lgdt instruction.
typedef struct gdt_ptr_st {
    uint16_t limit;    // Limit of the table (ie. its size)
    uint32_t base;     // Address of the first entry
} __attribute__((packed)) gdt_ptr_t;

extern void gdt_init();
extern void gdt_flush(gdt_ptr_t *gdt_ptr);

extern int exec_task(char* filename);
extern void setup_task(int id);

extern void setup_task_original();

#endif
