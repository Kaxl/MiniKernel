// To avoid warnings if an argument is not used.
// Example:
// void f(int arg) {
//     UNUSED(arg);
// }

#define UNUSED(x) ((void)(x))

#include "../common/syscall_nb.h"
#include "../common/types.h"

#include "../common/pfs.h"
#include "gdt.h"
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "x86.h"


int syscall_putc(char c);
int syscall_puts(char* s);
int syscall_exec();
int syscall_getc();
int syscall_file_stat(char* filename, stat_t* stat);
int syscall_file_read(char* filename, void* buf);
int syscall_file_remove(char* filename);
int syscall_file_iterator(file_iterator_t* it);
int syscall_file_next(char* filename, file_iterator_t *it);
unsigned int syscall_get_ticks();


// System call handler: call the appropriate system call according to the nb argument.
// Called by the assembly code _syscall_handler
int syscall_handler(syscall_t nb, uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4, uint32_t caller_tss_selector) {

    // First address of the task which called the syscall
    char* addr = (char*)(LIMIT_SIZE * (SELECTOR_TO_GDT_INDEX(caller_tss_selector) - FIRST_TASK_ENTRY) / 2 + FIRST_TASK_ADDR);

    switch (nb) {

        case SYSCALL_PUTC:
            UNUSED(arg2);
            UNUSED(arg3);
            UNUSED(arg4);
            return syscall_putc((char*)(addr + arg1));
            break;

        case SYSCALL_PUTS:
            UNUSED(arg2);
            UNUSED(arg3);
            UNUSED(arg4);
            return syscall_puts((char*)(addr + arg1));
            break;

        case SYSCALL_EXEC:
            printf("[syscall] addr %x\n", addr);
            UNUSED(arg3);
            UNUSED(arg4);
            return syscall_exec((char*)(addr + arg1), (char*)(addr + arg2));
            break;

        case SYSCALL_GETC:
            UNUSED(arg1);
            UNUSED(arg2);
            UNUSED(arg3);
            UNUSED(arg4);
            return syscall_getc();
            break;

        case SYSCALL_FILE_STAT:
            UNUSED(arg3);
            UNUSED(arg4);
            syscall_file_stat((char*)(addr + arg1), (stat_t*)arg2);
            break;

        case SYSCALL_FILE_READ:
            break;

        case SYSCALL_FILE_REMOVE:
            break;

        case SYSCALL_FILE_ITERATOR:
            break;

        case SYSCALL_FILE_NEXT:
            break;

        case SYSCALL_GET_TICKS:
            break;

        case __SYSCALL_END__:
        default:
            return -1;
    }

    return -1;
}

int syscall_putc(char c) {
    printCharacter(c);
    return 0;
}

int syscall_puts(char* s) {
    printString(s);
    return 0;
}

int syscall_exec(char* filename) {
    if (exec_task(filename) < 0)
        return -1;
    return 0;
}

int syscall_getc() {
    return getc();
}

int syscall_file_stat(char* filename, stat_t* stat) {
    return file_stat(filename, stat);
}

int syscall_file_read(char* filename, void* buf) {
    return file_read(filename, buf);
}

int syscall_file_remove(char* filename) {
    return file_remove(filename);
}

int syscall_file_iterator(file_iterator_t* it) {
    *it = file_iterator();
    return 0;
}

int syscall_file_next(char* filename, file_iterator_t* it) {
    return file_next(filename, it);
}

unsigned int syscall_get_ticks() {
    return get_ticks();
}
