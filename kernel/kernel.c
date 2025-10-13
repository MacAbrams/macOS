#include <stdint.h>
#include <kernel/tty.h>
#include "vga.h"
#include <string.h>
#include <stdio.h>
#include <gdt.h>
#include <idt.h>
#include <timer.h>

extern uint8_t inb(int port);
extern int outb(int port,int data);


void testFunc(struct InterruptRegisters* regs){
	uint8_t scan = inb(0x60);
	scan+=0x65-0x1e;
	// 0000 0000
	// 1: release
	printf("handler: %x\n",scan);
	outb(0x20,0x20);
}


int main(void){
	terminal_initialize();
	printf("test1\n");
	initGdt();
	printf("test2\n");
	initIdt();
	printf("test3\n");
	initTimer();
//	irq_install_handler(0,testFunc);
	//irq_install_handler(1,testFunc);


	while(1){
	
	}
	return 0;
}
