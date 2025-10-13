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
	mov dx, [esp + 0x8]
	mov ax, [esp + 12]
	out dx, al
	pop edx
	ret
global inb
; inb(port)
inb:
	push edx
	mov dx, [esp + 0x8]
	in al, dx
	pop edx
	ret
