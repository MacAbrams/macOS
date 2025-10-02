#include <string.h>

void* memset(void* s, int fill, size_t size){
	for(size_t i=0; i<size; ++i){
		((char*)s)[i]=(char)fill;
	}
	return s;
}
