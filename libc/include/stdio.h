#ifndef STDIO_H
#define STDIO_H 1

#include <sys/cdefs.h>

int printf(const char* __restrict s, ...);
int putchar(char c);
int puts(const char* s);

#endif
