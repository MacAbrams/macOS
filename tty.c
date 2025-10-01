#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include <tty.h>
#include "vga.h"

extern void outb(uint8_t value, uint16_t port);


static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY =(uint16_t*) 0xb8000;

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;

void terminal_setcursor(size_t x, size_t y){
	size_t i = x + y * VGA_WIDTH;

	outb(0xf,0x3d4);	
	outb(i&0xff,0x3d5);	
	outb(0xe,0x3d4);	
	outb((i>>8)&0xff,0x3d5);	
}

void terminal_initialize(void){
	terminal_buffer = VGA_MEMORY;
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_WHITE,VGA_COLOR_RED);
	terminal_setcursor(0,0);
	for(size_t i=0; i<VGA_HEIGHT*VGA_WIDTH; ++i){
		terminal_buffer[i] = vga_entry(' ',terminal_color);
	}
}

void terminal_setcolor(uint8_t c){
	terminal_color = c;
}

void terminal_putentryat(unsigned char c, uint8_t col, size_t x, size_t y){
	terminal_buffer[x + y * VGA_WIDTH] = vga_entry(c,col);
}

void terminal_scroll(int line){
	char c;

	for(size_t loop = line * (VGA_WIDTH * 2) + 0xb8000; loop < VGA_WIDTH * 2; ++loop){
		c = *(uint16_t*)loop;
		*(uint16_t*)(loop - (VGA_WIDTH)) = c;
	}
}

void terminal_delete_last_line(){
	for(size_t i = 0; i < VGA_WIDTH; ++i){
		terminal_buffer[i]=vga_entry(' ',terminal_color);
	}
}

void terminal_putchar(char c){
	terminal_putentryat(c,terminal_color,terminal_column, terminal_row);
	if(++terminal_column == VGA_WIDTH){
		terminal_column = 0;
		if(++terminal_row == VGA_HEIGHT){
			for(size_t line = 1; line <=VGA_HEIGHT-1; ++line){
				terminal_scroll(line);
			}
			terminal_delete_last_line();
			terminal_row = VGA_HEIGHT-1;
		}
	}
}
void terminal_write(const char* data, size_t size){
	for(size_t i = 0; i<size; ++i){
		terminal_putchar(data[i]);
	}
}
void terminal_writestring(const char* s);
