#ifndef TTY_H
#define TTY_H 1
#include <stddef.h>

void terminal_setcolumn(int x);
void terminal_setrow(int y);
void terminal_newline();
void terminal_tab();


void terminal_initialize(void);
void terminal_putchar(char c);
void terminal_write(const char* s, size_t size);
void terminal_writestring(const char* s);

#endif
