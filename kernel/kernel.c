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

int main(uint32_t memInfo){
	//detect memory

	terminal_initialize();
	initGdt();
	initIdt();
	initTimer();
//	irq_install_handler(0,testFunc);
//	initKeys();
	
	printf("%p\n",memInfo);
	size_t num = *((size_t*)memInfo);
	struct physical_memory_table_entry* entries = ((struct physical_memory_table_entry**)memInfo)[1];

	printf("%x:\n",num);
	for(size_t i=0;i<num; ++i){
		printf("Base: %llx  L: %llx R: %x A: %x\n",entries[i].base,entries[i].length,entries[i].region,entries[i].ACPI);
	}


	while(1){
	
	}
	return 0;
}
