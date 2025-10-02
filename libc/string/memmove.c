#include <string.h>

void* memmove(void* dst, const void* src, size_t size){
	if(dst < src){
		for(size_t i=0; i< size; ++i){
			((char*)dst)[i]=((char*)src)[i];
		}
	}
	else{
		for(size_t i=size; i>0; --i){
			((char*)dst)[i-1]=((char*)src)[i-1];
		}
	}
	return dst;
}
