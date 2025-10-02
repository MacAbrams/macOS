#include <stdio.h>
#include <stdarg.h>

int printf(const char * s, ...){
	va_list param;
	va_start(param, s);
	int i=0;
	while(s[i]!=0){
		//format time
		if(s[i]=='%'){
			++i;
			switch(s[i]){
				case('%'):
					putchar('%');
					++i;
					break;
				case('c'):
					putchar((char)va_arg(param, int));
					++i;
					break;

			}

		}
		putchar(s[i]);
		++i;
	}
	va_end(param);
	return 0;
}
