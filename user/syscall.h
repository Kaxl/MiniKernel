#ifndef _SYSCALL_H_
#define _SYSCALL_H_

/**
 * @brief Call the syscall asm code
 *
 * @param nb Syscall number
 * @param arg1 First arg
 * @param arg2 Secong arg
 * @param arg3 Third arg
 * @param arg4 Fourth arg
 *
 * @return What the syscall called will return
 */
extern int syscall(uint32_t nb, uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4);

#endif
