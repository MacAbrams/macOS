global _start
_start:
	push ebp
	mov ebp, esp

	[extern main]
	call main
	mov esp, ebp
	pop ebp
