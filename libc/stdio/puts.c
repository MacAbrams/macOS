#include <stdio.h>

int puts(const char* s){
	int i=0;
	while(s[i]!=0){
		putchar(s[i]);
		++i;
	}
	return i;
}
