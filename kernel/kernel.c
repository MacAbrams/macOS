#include <stdint.h>
#include <tty.h>
#include "vga.h"
#include <string.h>


int main(void){
	terminal_initialize();
	terminal_putchar('a');
	terminal_putchar(0xa);
	char* s = "test\nnow";

	terminal_write(s,strlen(s));
	while(1){
	
	}
	return 0;
}
