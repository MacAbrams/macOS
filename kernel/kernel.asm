section .boot
global _start
_start:
	
	mov eax, 0x0
	mov ebx, 0x1000
	.fill_table:
		mov ecx, ebx
		or ecx, 3
		mov [initial_page_dir+eax*4],ecx
		add ebx, 4096
		inc eax
		cmp eax, 1024
		jne .fill_table
	.done:
	jmp higher_half
		
	mov eax, (initial_page_dir - 0xc0000000)
	mov cr3, eax ;tells where the page table is
	mov ecx, cr4
	or ecx, 0x10 ; physical address extension on
	mov cr4, ecx

	mov ecx, cr0
	or ecx, 0x80000000 ;enable paging
	mov cr0, ecx
	mov ecx, cr0
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
align 4096
global initial_page_dir
initial_page_dir: 
 ;PavlGpDappurp
	dd 0x100003
	times 768-1 dd 0
	;kernel
	dd (0 << 22) | 0x100003
	dd (1 << 22) | 0x100003
	dd (2 << 22) | 0x100003
	dd (3 << 22) | 0x100003
	times 256-4 dd 0
