#include "../common/types.h"
#include "gdt.h"
#include "x86.h"

// TODO: déclarer la table GDT

// Pointeur sur la table GDT
static gdt_ptr_t   gdt_ptr;

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
static gdt_entry_t null_segment() {
	gdt_entry_t entry;
    memset(&entry, 0, sizeof(gdt_entry_t));
	return entry;
}

// Return a code segment specified by the base, limit and privilege level passed in arguments.
static gdt_entry_t code_segment(uint32_t base, uint32_t limit, uint8_t dpl) {
    return build_entry(base, limit, TYPE_CODE_EXECREAD, S_CODE_OR_DATA, DB_SEG, 1, dpl);
}

// Return a data segment specified by the base, limit and privilege level passed in arguments.
static gdt_entry_t data_segment(uint32_t base, uint32_t limit, uint8_t dpl) {
    return build_entry(base, limit, TYPE_DATA_READWRITE, S_CODE_OR_DATA, DB_SEG, 1, dpl);
}

// Initialize the GDT
void gdt_init() {
	// TODO: fixer la limite de gdt_ptr, puis la faire pointer sur la GDT

	// TODO: initialisation des trois descripteurs de segment: NULL, segment code, segment data
	// Les descripteurs de code et data doivent avoir un DPL de 0.

    // Load the GDT
    gdt_flush(&gdt_ptr);
}

