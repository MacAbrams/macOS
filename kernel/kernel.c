#include <stdint.h>
#include <kernel/tty.h>
#include "vga.h"
#include <string.h>
#include <stdio.h>
#include <gdt.h>
#include <idt.h>


int main(void){
	terminal_initialize();
	printf("test1\n");
	initGdt();
	printf("test2\n");
	initIdt();
	printf("test3\n");


	while(1){
	
	}
	return 0;
}
