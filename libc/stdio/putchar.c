#include <stdio.h>
#include <kernel/tty.h>
int putchar(char c){
	terminal_putchar(c);
	return 0;
}
