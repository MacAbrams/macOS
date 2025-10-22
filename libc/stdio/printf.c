#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

int printf(const char * s, ...){
	va_list param;
	va_start(param, s);
	size_t written = 0;
	int i=0;
	while(s[i]!=0){
		//format time
		if(s[i]=='%'){
			++i;
			unsigned char length = sizeof(int);
			char* a;
			switch(s[i]){
				case('h'):
					length = sizeof(short);
					if(s[i]=='h'){
						length = sizeof(char);
						++i;
					}
					continue;
				case('l'):
					length = sizeof(long);
					if(s[i]=='l'){
						length = sizeof(long long);
						++i;
					}
					continue;
				case('J'):
					length = sizeof(uintmax_t);
					continue;
				case('z'):
					length = sizeof(size_t);
					continue;
				case('t'):
					length = sizeof(ptrdiff_t);
					continue;

				case('%'):
					putchar('%');
					++written;
					break;
				case('c'):
					putchar((char)va_arg(param, int));
					++written;
					break;
				case('s'):
					written+=puts(va_arg(param, char*));
					break;
				case('d'):
				case('i'):
					//todo
					puts("Dec");
					break;
				case('o'):
					//octal
					break;
				case('x'):
				case('X'):
					//hex
					if(length<sizeof(int)){
						*(int*)a = va_arg(param, int);
					}	
					else if(length == sizeof(long)){
						*(long*)a = va_arg(param, long);
					}
					else if(length == sizeof(long long)){
						*(long long*)a = va_arg(param, long long);
					}
					else{
						break;
					}
					written+=length*2+2;
					putchar('0');
					putchar(s[i]);
					int offset = 0x37+(s[i]&0x20);
					while(length>0){
						length-=1;
						char c = a[length];
						char b = c>>4;
						c &=0xf;
						b &=0xf;
						c+=c>0x9?offset:0x30;
						b+=b>0x9?offset:0x30;
						putchar(b);
						putchar(c);
					}
					break;
				case('p'):
					//ptr
					void** ap;
					*ap = va_arg(param, void*);
					written+=length*2+2;
					putchar('0');
					putchar('x');
					while(length>0){
						length-=1;
						char c = ((char*)ap)[length];
						char b = c>>4;
						c &=0xf;
						b &=0xf;
						c+=c>0x9?0x37:0x30;
						b+=b>0x9?0x37:0x30;
						putchar(b);
						putchar(c);
					}
					break;
				//not doing floats yet
				case('n'):
					*va_arg(param, int*) = written;
					break;	
			}
			++i;
			if(s[i]==0){
				return 0;
			}

		}
		putchar(s[i]);
		++written;
		++i;
	}
	va_end(param);
	return 0;
}
