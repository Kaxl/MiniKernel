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

#define BUF_SIZE 100

extern void main();

extern void ls();

extern void cat(char* filename);

extern void rm(char* filename);

extern void run(char* filename);

extern void ticks();

extern void help();

#endif
