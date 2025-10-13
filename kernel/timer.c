#include <timer.h>
#include <stdio.h>

extern void outb(int data, int port);
extern uint8_t inb(int port);

uint64_t ticks; // one tick is one irq0
const uint32_t freq = 100;


void initTimer(){
	ticks=0;
	irq_install_handler(0,onIrq0);

	//1.193181666 MHz = 1193181 Hz
	uint32_t divisor = 1193180/freq;
	
	//0011 0110
	//channel 0, lo/hi, square, 16bit binary
	outb(0x36,0x43);
	outb((uint8_t)(divisor & 0xff),0x40);
	outb((uint8_t)((divisor >> 8) & 0xff),0x40);

}
void onIrq0(struct InterruptRegisters *regs){
	ticks++;
}
