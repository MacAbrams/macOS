#include <stdint.h>
#include <tty.h>
#include "vga.h"


int main(void){
	terminal_initialize();
	terminal_putchar('a');
	terminal_putchar(0xa);
	terminal_write("testing\n",8);
	while(1){
	
	}
	return 0;
}
