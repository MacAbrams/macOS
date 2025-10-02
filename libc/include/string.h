#ifndef STRING_H
#define STRING_H 1
#include <stdint.h>
#include <stddef.h>

int memcmp(const void* a, const void* b, size_t size);
void* memcpy(void* __restrict, const void* __restrict, size_t size);
void* memmove(void*, const void*, size_t);
void* memset(void* s, int fill, size_t size);
size_t strlen(const char* s);

#endif
