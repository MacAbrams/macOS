#include <string.h>

void* memcpy(void* restrict dst, const void* restrict src, size_t size){
	for(size_t i=0; i<size; ++i){
		((char*)dst)[i]=((char*)src)[i];
	}
	return dst;
}
