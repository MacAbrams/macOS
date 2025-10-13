#ifndef TIMER_H
#define TIMER_H 1
#include <idt.h>

void initTimer();
void onIrq0(struct InterruptRegisters *regs);


#endif
