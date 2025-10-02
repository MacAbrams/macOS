#include <string.h>

int memcmp(const void* a, const void* b, size_t size){
	for(size_t i=0; i<size; ++i){
		if(((unsigned char*)a)[i]<((unsigned char*)b)[i]){
			return -1;	
		}
		if(((unsigned char*)a)[i]>((unsigned char*)b)[i]){
			return 1;	
		}
	}
	return 0;
}
