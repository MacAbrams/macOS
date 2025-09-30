global _start
_start:
	mov byte [0xb8000],'E'
	[extern main]
	call main
