#include <stdint.h>
#include <kernel/tty.h>
#include "vga.h"
#include <string.h>
#include <stdio.h>
#include <gdt.h>
#include <timer.h>
#include <keys.h>
#include <mem.h>
#include <paging.h>
/*
 * current Memory
 * 0x00000
 * IVT
 * 0x00400
 * BDA
 * 0x00500
 * possible stage 2??
 * 0x01000
 * _start
 * os
 * ||
 * \/
 *
 * 0x07c00
 * boot
 * 0x07e00
 * mmap
 * || 
 * \/
 *
 * /\
 * ||
 * stack
 * 0x9000
 * Page Dir
 * 0xA000
 * Page Table table
 * 0xB000
 * TBD (4 kiB)
 * ||
 * \/
 * 
 * 0x80000
 * EBDA (uint16_t size = *0x413)
 * ||
 * \/
 *
 * /\
 * ||
 * stack
 * 0xA0000
 * ISA Hole
 * 0x100000
 * 1MiB
 *
 * end ID Map 4MiB boundry
 * 0x3FFFFF
 *
 */


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
	printf("Boot succesful\n");
	initGdt();
	initIdt();
	initTimer();
	initPaging();
//	irq_install_handler(0,testFunc);
	initKeys();

	uint32_t num = *memInfo;
	struct physical_memory_table_entry* entries = (struct physical_memory_table_entry*)(&memInfo[1]);	
	printf("%x\n",num);
	for(size_t i=0; i<(size_t)num;++i){
		struct physical_memory_table_entry e = entries[i]; 
		if(e.region == 1){
			printf("%llx, %llx, %lx\n",e.base,e.length,e.region);
		}
		uint32_t start = e.base;
		uint32_t end = e.base+e.length;

	}



	
	while(1){
		asm("nop");		
	}
	return 0;
}
