/*
 * =====================================================================================
 *
 *       Filename:  controller.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  11/17/2015 11:22:12 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Axel Fahy, Rudolf Hohn
 *   Organization:  HES-SO hepia section ITI
 *
 * =====================================================================================
 */

#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

// Functions written in controller_asm.s
extern void outb(ushort port, uchar data);

extern void outw(ushort port, ushort data);

extern uchar inb(ushort port);

extern ushort inw(ushort port);

#endif
