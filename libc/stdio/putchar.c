#include <stdio.h>
#include <kernel/tty.h>
int putchar(char c){
	switch(c){
		case(0x9):
			terminal_tab();
			break;
		case(0xa):
			terminal_newline();
			terminal_setcolumn(0);
			break;
		default:
			terminal_putchar(c);
			break;
	}
	return 0;
}
