#include <stdint.h>
#include <kernel/tty.h>
#include "vga.h"
#include <string.h>
#include <stdio.h>


int main(void){
	terminal_initialize();
	printf("test %% %c\n",'a');

	while(1){
	
	}
	return 0;
}
