section .boot
global _start
_start:
	mov esp, 0x8ff0
	push ebx
	mov  byte [0xb8000], 'B'
	;mov esp, 0x9000 
	mov esp, 0xc00000
	mov dword[esp], 10000011b ; identity page
	add esp, 4
	mov ecx, 768-1
	.l1:
		mov dword[esp], 0
		add esp, 4
		loop .l1
		mov dword[esp], (kernel_page_table) + 00000011b
		add esp, 4
		mov dword[esp], (1 << 22) | 10000011b
		add esp, 4
		mov dword[esp], (2 << 22) | 10000011b
		add esp, 4
		mov dword[esp], (3 << 22) | 10000011b
		add esp, 4
	mov ecx, 256-4
	.l2:
		mov dword[esp], 0
		add esp, 4
		loop .l2
	; weve used 4096 bytes aka 0x1000 so we at 0xc01000
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

	mov byte [0xb8002],'3'
	mov eax, (0xc00000)
	mov cr3, eax ;tells where the page table is
;
	mov byte [0xb8002],'4'
	mov ecx, cr4
	or ecx, 0x10 ; physical address extension on
	mov cr4, ecx

	mov byte [0xb8002],'0'
	mov ecx, cr0
	or ecx, 0x80000001 ;enable paging
	mov cr0, ecx
	mov ecx, cr0

	mov ecx, cr0
	and ecx, 0x80000001 ;enable paging
	cmp ecx, 0
	jne .yay
	mov byte [0xb8004],'f'
	hlt
	
	.yay:
	mov byte [0xb8004],'s'

	jmp higher_half


section .text
higher_half:
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


;this can be a function not a predifined section
section .data
global initial_page_dir
align(4096)
initial_page_dir: 
 ;PavlGpDappurp
	dd 10000011b ; identity page
	times 768-1 dd 0
	;kernel
	dd (kernel_page_table) + 00000011b
	dd (1 << 22) | 10000011b
	dd (2 << 22) | 10000011b
	dd (3 << 22) | 10000011b
	times 256-4 dd 0

align(4096)
kernel_page_table:
;      avlgpdapprp 
	dd (1 << 12) | 00000000011b
	dd (2 << 12) | 00000000011b
	dd (3 << 12) | 00000000011b
	times 1024-3 dd 0
global testingSym
testyngSym: db 0x66,0xbb
