section .boot
global _start
_start:
	mov  byte [0xb8000], 'B'
	push ebx
	jmp higher_half
		
	mov eax, (initial_page_dir - 0xc0000000)
	mov cr3, eax ;tells where the page table is
	mov ecx, cr4
	or ecx, 0x10 ; physical address extension on
	mov cr4, ecx

	mov ecx, cr0
	or ecx, 0x80000001 ;enable paging
	mov cr0, ecx
	jmp higher_half


section .text
higher_half:
	mov esp, stack_top 
	push ebx ;info from boot
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


global getLowMemory
getLowMemory:
	;get from 0x8000
	mov eax, 0x8000	
	ret

section .bss
stack_bottom:
	resb 16384 * 8
stack_top:


section .data
global initial_page_dir
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

kernel_page_table:
;      avlgpdapprp 
	dd (1 << 12) | 00000000011b
	dd (2 << 12) | 00000000011b
	dd (3 << 12) | 00000000011b
	times 1024-3 dd 0
