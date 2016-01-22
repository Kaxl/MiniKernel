/*
 * =====================================================================================
 *
 *       Filename:  shell.h
 *
 *    Description:  Header file of shell.c
 *
 *        Version:  1.0
 *        Created:  01/11/2016 07:47:28 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Rudolf Hohn, Axel Fahy
 *   Organization:  HES-SO hepia section ITI
 *
 * =====================================================================================
 */

#ifndef __SHELL_H
#define __SHELL_H

// Buffer for the CLI
#define BUF_SIZE        100
#define SHELL_SCREEN    "shell.txt"

/**
 * @brief Entry point of the shell
 *
 * @param
 *
 * @return
 */
extern void main();

/**
 * @brief List all files on the disks
 *
 * @param
 *
 * @return
 */
extern void ls();

/**
 * @brief Print the content of a file
 *
 * @param filename
 *
 * @return
 */
extern void cat(char* filename);

/**
 * @brief Delete a file from the disk
 *
 * @param filename
 *
 * @return
 */
extern void rm(char* filename);

/**
 * @brief Run a programm
 *
 * @param filename  The programm to execute
 *
 * @return
 */
extern void run(char* filename);

/**
 * @brief Display the current ticks count of the system
 *
 * @param
 *
 * @return
 */
extern void ticks();

/**
 * @brief Display the help
 *
 * @param
 *
 * @return
 */
extern void help();

#endif
