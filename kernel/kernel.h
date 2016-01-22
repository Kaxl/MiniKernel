/*
 * =====================================================================================
 *
 *       Filename:  kernel.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  10/16/2015 11:22:12 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Axel Fahy, Rudolf Hohn
 *   Organization:  HES-SO hepia section ITI
 *
 * =====================================================================================
 */

#ifndef _KERNEL_H_
#define _KERNEL_H_

// Default frequency for timer
#define DEFAULT_FREQ 100

#define SPLASH_FILE "splash_screen"

/**
 * @brief Start the kernel
 *
 * Function call by the assembly file : 'bootloader.s'
 * Initialize the kernel, print a splash screen and start a shell
 */
extern void runKernel();

#endif
