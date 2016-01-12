// To avoid warnings if an argument is not used.
// Example:
// void f(int arg) {
//     UNUSED(arg);
// }

#define UNUSED(x) ((void)(x))

#include "../common/syscall_nb.h"
#include "../common/types.h"

#include "../common/pfs.h"
#include "screen.h"
#include "keyboard.h"
#include "timer.h"


void syscall_putc(char c);
void syscall_puts(char* s);
void syscall_exec();
char syscall_getc();
int syscall_file_stat(char* filename, stat_t* stat);
int syscall_file_read(char* filename, void* buf);
int syscall_file_remove(char* filename);
int syscall_file_iterator(file_iterator_t* it);
int syscall_file_next(char* filename, file_iterator_t *it);
unsigned int syscall_get_ticks();


// System call handler: call the appropriate system call according to the nb argument.
// Called by the assembly code _syscall_handler
int syscall_handler(syscall_t nb, uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4, uint32_t caller_tss_selector) {

    switch (nb) {

        case SYSCALL_PUTC:
            UNUSED(arg2);
            UNUSED(arg3);
            UNUSED(arg4);
            syscall_putc((char)arg1);
            break;

        case SYSCALL_PUTS:
            UNUSED(arg2);
            UNUSED(arg3);
            UNUSED(arg4);
            syscall_puts((char*)arg1);
            break;

        case SYSCALL_EXEC:
            break;

        case SYSCALL_GETC:
            UNUSED(arg1);
            UNUSED(arg2);
            UNUSED(arg3);
            UNUSED(arg4);
            syscall_getc();
            break;

        case SYSCALL_FILE_STAT:
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

void syscall_putc(char c) {
    printCharacter(c);
}

void syscall_puts(char* s) {
    printString(s);
}

void syscall_exec() {
//
}

char syscall_getc() {
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
