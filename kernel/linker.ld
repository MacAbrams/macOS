ENTRY(_start)
SECTIONS
{
	.boot 0x1000:{
		*(.boot)
	}
	.text : AT(ADDR(.text)){
		*(.text)
	}
	.bss : AT(ADDR(.bss)){
		*(COMMON)
	}
	.data : AT(ADDR(.data)){
		. = ALIGN(4096);
		*(.data)
	}

	_kernel_end = .;
}
