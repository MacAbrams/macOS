global _start
_start:
	push ebp
	mov ebp, esp

	[extern main]
	call main
	mov esp, ebp
	pop ebp
global outb
outb:
	push edx
	mov ax, [esp + 0x8]
	mov dx, [esp + 12]
	out dx, al
	pop edx
	mov eax, 0
	ret
