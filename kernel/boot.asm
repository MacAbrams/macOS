[BITS 16]
[ORG 0x7c00]

KernelLocation equ 0x1000
NUM_SECTORS equ 5

start:
	cli
	mov [diskname], dl
	mov ax, 0x0
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov sp, 0x7c00
	mov bp, sp
	sti
load:
	mov dl, [diskname]
	mov ch, 0
	mov dh, 0
	mov cl, 2
	mov al, NUM_SECTORS
	mov bx, KernelLocation
	mov ah, 2
	int 0x13

	lea si, [fileError]
	jc error
	lea si, [msg2]
	cmp al, NUM_SECTORS
	jne error
	jmp enter_protected
msg2: db "Wrong number of sectors read",0xd,0xa,0
	error:
	.l1:
		lodsb
		cmp al, 0
		je .done
		mov ah, 0x0E
		int 0x10
		jmp .l1
	.done:
	cli
	hlt
	jmp $	
enter_protected:
	cli
	lgdt [GDT_descriptor]
	mov eax, cr0
	or eax, 1
	mov cr0, eax
	mov eax, cr0
	bt eax, 0
	lea si, [protectedError]
	jnc error
	jmp CODESEG:start_protected_mode
GDT_start:
	null_descriptor:
		dd 0,0
	code_descriptor:
		dw 0xffff ; limit
		dw 0 ; base
		db 0 ; base
		db 0b10011010 ; pres, type
		db 0b11001111 ; other
		db 0 ; base
	data_descriptor:
		dw 0xffff ; limit
		dw 0 ; base
		db 0 ; base
		db 0b10010010 ; pres, type
		db 0b11001111 ; other
		db 0 ; base
GDT_end:
GDT_descriptor:
	dw GDT_end - GDT_start - 1 ;size
	dd GDT_start ; start

CODESEG equ code_descriptor - GDT_start
DATASEG equ data_descriptor - GDT_start

[bits 32]
start_protected_mode:
	mov ax, DATASEG
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ebp, 0x90000
	mov esp, ebp
	mov byte [0xb8000],"A"
	jmp KernelLocation

	cli
	hlt

	
diskname: dd 0
msg: db "test",0xd,0xa,0
fileError: db "file error",0xd,0xa,0
protectedError: db "prot error",0xd,0xa,0

times 510 - ($ -$$) db 0
dw 0xAA55
