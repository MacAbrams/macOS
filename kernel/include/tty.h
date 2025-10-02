#ifndef TTY_H
#define TTY_H
#include <stddef.h>

void terminal_initialize(void);
void terminal_putchar(char c);
void terminal_write(const char* s, size_t size);
void terminal_writestring(const char* s);

#endif
