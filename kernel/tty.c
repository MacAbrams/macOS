#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include <kernel/tty.h>
#include "vga.h"

extern void outb(int port, int data);


static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY =(uint16_t*) 0xb8000;

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;

void terminal_setcursor(size_t x, size_t y){
	size_t i = x + y * VGA_WIDTH;

	outb(0x3d4, 0xf);
	outb(0x3d5, i&0xff);
	outb(0x3d4, 0xe);
	outb(0x3d5, (i>>8)&0xff);
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

void terminal_setcolumn(int x){
	terminal_column = x;
}

void terminal_setrow(int y){
	terminal_row = y;
}

void terminal_putentryat(unsigned char c, uint8_t col, size_t x, size_t y){
	unsigned int a = x + y * VGA_WIDTH;
	if(a<VGA_HEIGHT*VGA_WIDTH){
		terminal_buffer[x + y * VGA_WIDTH] = vga_entry(c,col);
	}
}

void terminal_scroll(int line){
	char c;

//	for(size_t loop = line * (VGA_WIDTH * 2) + 0xb8000; loop < VGA_WIDTH * 2; ++loop){
//		c = *(uint16_t*)loop;
//		*(uint16_t*)(loop - (VGA_WIDTH)) = c;
//	}
	if((unsigned int)line < VGA_HEIGHT && line!=0){
	for(size_t i = 0; i<VGA_WIDTH*2;++i){
		c = *(uint16_t*)((uint32_t)0xb8000+2*VGA_WIDTH*line+i);
		*(uint16_t*)((uint32_t)0xb8000+2*VGA_WIDTH*(line-1)+i) = c;
	}
	}
}

void terminal_delete_last_line(){
	for(size_t i = 0; i < VGA_WIDTH; ++i){
		terminal_buffer[VGA_WIDTH*(VGA_HEIGHT-1)+i]=vga_entry(' ',terminal_color);
	}
}

void terminal_newline(){
	if(++terminal_row == VGA_HEIGHT){
		for(size_t line = 1; line <=VGA_HEIGHT-1; ++line){
			terminal_scroll(line);
		}
		terminal_delete_last_line();
		terminal_row = VGA_HEIGHT-1;
	}
}

void terminal_tab(){
	terminal_column=(terminal_column+4)&(~0x3);
	if(terminal_column == VGA_WIDTH){
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

void terminal_putchar(char c){
	switch(c){
		case(0x9):
			terminal_tab();
			break;
		case(0xa):
			terminal_newline();
			terminal_setcolumn(0);
			break;
		default:
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

			break;
	}
	terminal_setcursor(terminal_column,terminal_row);

}
void terminal_write(const char* data, size_t size){
	for(size_t i = 0; i<size; ++i){
		terminal_putchar(data[i]);
	}
}
void terminal_writestring(const char* s);
