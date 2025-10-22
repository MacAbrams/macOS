#include <keys.h>
#include <stdio.h>

extern uint8_t inb(int port);
extern int outb(int port,int data);
const unsigned char keymap[128] = {0,0x1b,'1','2','3','4','5','6','7','8','9','0','-','=','\b','\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',0,'a','s','d','f','g','h','j','k','l',';','\'','`',0,'\\','z','x','c','v','b','n','m',',','.','/',0,'*',0,' ',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'-',0,0,0,'+'};
const unsigned char keymapShift[128] = {0,0x1b,'!','@','#','$','%','^','&','*','(',')','_','+','\b','\t','Q','W','E','R','T','Y','U','I','O','P','{','}','\n',0,'A','S','D','F','G','H','J','K','L',':','\"','~',0,'|','Z','X','C','V','B','N','M','<','>','?',0,'*',0,' ',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'-',0,0,0,'+'};

uint8_t shift = 0;
uint8_t caps = 0;

void initKeys(){
	irq_install_handler(1,keyPressHandler);
}

void keyPressHandler(struct InterruptRegisters* regs){
	uint8_t scan = inb(0x60);
	//scan+=0x65-0x1e;
	// 0000 0000
	// 1: release
	
	switch(scan){
		case(0):
		case(KEY_L_CTRL_PRESSED):
			break;
		case(KEY_L_SHIFT_PRESSED):
		case(KEY_R_SHIFT_PRESSED):
			shift = 1;
			break;
		case(KEY_L_ALT_PRESSED):
		case(KEY_CAPSLOCK_PRESSED):
			caps ^=1;
			break;
		case(KEY_F1_PRESSED):
		case(KEY_F2_PRESSED):
		case(KEY_F3_PRESSED):
		case(KEY_F4_PRESSED):
		case(KEY_F5_PRESSED):
		case(KEY_F6_PRESSED):
		case(KEY_F7_PRESSED):
		case(KEY_F8_PRESSED):
		case(KEY_F9_PRESSED):
		case(KEY_F10_PRESSED):
		case(KEY_NUMLOCK_PRESSED):
		case(KEY_SCROLLLOCK_PRESSED):
		case(KEY_F11_PRESSED):
		case(KEY_F12_PRESSED):
			break;
		case(KEY_BACKSPACE_PRESSED):
			break;
		case(0xe0):
			outb(0x20,0x20);
			uint8_t scan2 = inb(0x60);
			printf("e0:%x",scan2);
			break;
		case(KEY_L_SHIFT_RELEASED):
		case(KEY_R_SHIFT_RELEASED):
			shift = 0;
			break;
		case KEY_Q_PRESSED ... KEY_P_PRESSED:
		case KEY_A_PRESSED ... KEY_L_PRESSED:
		case KEY_Z_PRESSED ... KEY_M_PRESSED:
			if(caps ^ shift){
				printf("%c",keymapShift[scan]);
			}
			else{
				printf("%c",keymap[scan]);
			}
			break;
		default:
			if((scan & 0x80) == 0){
				if(shift){
					printf("%c",keymapShift[scan]);
				}
				else{
					printf("%c",keymap[scan]);
				}
			}
			break;
		
	}

	outb(0x20,0x20);
}
