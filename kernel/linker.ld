ENTRY(_start)
SECTIONS
{
	.boot 0x1000 :
	{
		*(.boot)
	}
	/*. += 0xc0000000;
	.text : AT(ADDR(.text)-0xc0000000){
		*(.text)
	}
	.bss : AT(ADDR(.bss)-0xc0000000){
		*(COMMON)
		*(.bss)
	}
	.data : AT(ADDR(.data)-0xc0000000){
		*(.data)
	}
	*/
	.text : AT(ADDR(.text)){
		*(.text)
	}
	.bss : AT(ADDR(.bss)){
		*(COMMON)
		*(.bss)
	}
	.data : AT(ADDR(.data)){
		*(.data)
	}

	_kernel_end = .;
}
