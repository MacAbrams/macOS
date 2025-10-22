#include <stdint.h>
#include <kernel/tty.h>
#include "vga.h"
#include <string.h>
#include <stdio.h>
#include <gdt.h>
#include <idt.h>
#include <timer.h>
#include <keys.h>
#include <mem.h>

extern uint8_t inb(int port);
extern int outb(int port,int data);

int main(void){
	//detect memory
	

	terminal_initialize();
	printf("test1\n");
	initGdt();
	printf("test2\n");
	initIdt();
	printf("test3\n");
	initTimer();
//	irq_install_handler(0,testFunc);
	initKeys();


	while(1){
	
	}
	return 0;
}
