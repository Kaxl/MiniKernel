#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

extern void keyboard_init();
extern void keyboard_handler();
extern int getc();

char ch_layout[256];

#endif
