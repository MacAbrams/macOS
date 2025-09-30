ARCH=/home/mac/opt/cross/bin/i686-elf
CC=${ARCH}-gcc
LD=${ARCH}-ld
AS=${ARCH}-as
CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra -Werror -g -m32
LDFLAGS:=$(LDFLAGS)
LIBS:=$(LIBS) -nostdlib -lk -lgcc

all:
	make boot
	make kernel

boot:
	nasm -fbin boot.asm -o boot.bin
	
kernel:
	nasm -felf kernel.asm -o kernel.asm.o
	$(CC) $(CFLAGS) -c kernel.c -o kernel.c.o
	$(LD) $(LDFLAGS) -Ttext 0x1000 kernel.asm.o kernel.c.o --oformat binary -g -o kernel.bin
	cat "boot.bin" "kernel.bin" > everythin.bin

