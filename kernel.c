#include <tty.h>
#include "vga.h"
int main(void){
	*(char*)(0xb8000)='A';
	while(1){
	
	}
	return 0;
}
