#include <stdint.h>
#include <kernel/tty.h>
#include "vga.h"
#include <string.h>
#include <stdio.h>
#include <gdt.h>
#include <timer.h>
#include <keys.h>
#include <mem.h>

extern uint8_t inb(int port);
extern int outb(int port,int data);
extern int _kernel_end;
extern int _kernel_sectors;

void dummy(void){
}
void condenseMemmap(size_t* num, struct physical_memory_table_entry* entries){
	for(size_t i=*num;i>0;i--){
		if(entries[i].region==entries[i-1].region && entries[i].base == entries[i-1].base+entries[i-1].length+1){
			entries[i-1].length+=entries[i].length;
			(*num)--;	
		}
	}	
}

uint8_t	*waitFlag = (uint8_t*)0x9010;	
void keyPress(struct InterruptRegisters* regs){
	uint8_t  scan = inb(0x60);
	if((scan & 0x80) ==0)
		*waitFlag = 1;	
	outb(0x20,0x20);
}

int main(uint32_t *memInfo){
	//detect memory
	terminal_initialize();
	printf("test1\n");
	initGdt();
	initIdt();
	initTimer();
//	irq_install_handler(0,testFunc);
	//initKeys();
	irq_install_handler(1,keyPress);
	
	printf("%p\n",memInfo);
	uint32_t num = *(memInfo);
	struct physical_memory_table_entry* entries = (struct physical_memory_table_entry*)(&memInfo[1]);
	printf("%x:\n",num);
	condenseMemmap(&num, entries);
	dummy();
	for(size_t i=0;i<num; ++i){
		*waitFlag = 0;
		printf("Base: %llx  L: %llx R: %x A: %x\n",entries[i].base,entries[i].length,entries[i].region,entries[i].ACPI);
		while(1){
			if(*waitFlag ==1){
				break;
			}
		}
	}


	//uint32_t end = (uint32_t)_kernel_end;
	
	//printf("%p: %x\n",&_kernel_end,end);
	printf("%x\n",*((uint32_t*)0x4070));
	while(1){
		asm("nop");		
	}
	return 0;
}
