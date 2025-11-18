section .boot
global _start
global kernel_page_dir
global kernel_page_table
_start:
	mov esp, 0x8ff0
	push ebx
	mov  byte [0xb8000], 'B'
	;mov esp, 0x9000 
	kernel_page_dir equ 0x9000
	mov esp, 0x9000
	mov dword[esp], 10000011b ; identity page
	add esp, 4
	mov dword[esp], (kernel_page_table) + 00000011b
	add esp, 4
	mov ecx, 1024-2
	.l1:
		mov dword[esp], 0
		add esp, 4
		loop .l1
	; weve used 4096 bytes aka 0x1000 so we at 0xA000
	kernel_page_table equ 0xA000
	mov dword[esp], (1 << 12) | 00000000011b
	add esp, 4
	mov dword[esp], (2 << 12) | 00000000011b
	add esp, 4
	mov dword[esp], (3 << 12) | 00000000011b
	add esp, 4
	
	mov ecx, 1024-3
	.l3:
	mov dword[esp], 0
	add esp, 4
	loop .l3

	mov eax, (kernel_page_dir)
	mov cr3, eax ;tells where the page table is
;
	mov ecx, cr4
	or ecx, 0x10 ; physical address extension on
	mov cr4, ecx

	mov ecx, cr0
	or ecx, 0x80000001 ;enable paging
	mov cr0, ecx

	jmp higher_half
db "tag1"


section .text
higher_half:
	nop ; i think the page directory overwrites this bit????
	mov esp, 0x8ff0
	push ebx
	xor ebp, ebp
	[extern main]
	call main
halt:
	hlt
	jmp $
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


