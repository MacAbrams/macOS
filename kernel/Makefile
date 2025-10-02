ARCH=/home/mac/opt/cross/bin/i686-elf
CC=${ARCH}-gcc
LD=${ARCH}-ld
AS=${ARCH}-as
AR=${ARCH}-ar

LIBDIR=../libc
INCLUDEDIR=./include
LIBINCLUDEDIR=$(LIBDIR)/include
DEBUG=../dbg


CFLAGS:=$(CFLAGS) -O0 -ffreestanding -Wall -Wextra  -g -m32 -I$(INCLUDEDIR) -I$(LIBINCLUDEDIR)
LDFLAGS:=$(LDFLAGS)
LIBS:=$(LIBS) -nostdlib -lk -lgcc


all:
	make boot
	make libs
	make kernel

boot:
	nasm -fbin boot.asm -o boot.bin
	
kernel:
	nasm -felf kernel.asm -o kernel.asm.o
#	$(CC) $(CFLAGS) -o $@ $(LINK_LIST)
	$(CC) $(CFLAGS) -c kernel.c -o kernel.c.o
	$(LD) $(LDFLAGS) -Ttext 0x1000 kernel.asm.o kernel.c.o tty.o $(LIBDIR)/libk.a --oformat binary -g -o kernel.bin
	$(LD) $(LDFLAGS) -Ttext 0x1000 kernel.asm.o kernel.c.o tty.o $(LIBDIR)/libk.a  -g -o $(DEBUG)/kernel.debug
	cat "boot.bin" "kernel.bin" "zero"> everything.bin
	objcopy kernel.asm.o $(DEBUG)/kernel.asm.debug
	objcopy kernel.c.o $(DEBUG)/kernel.c.debug
libs:
	$(CC) $(CFLAGS) -c -D_STATIC_LIB=1 tty.c -o tty.o
	objcopy tty.o $(DEBUG)/tty.debug
	$(AR) r libtty.a tty.o
	ranlib libtty.a

clean:
	rm *.o *.bin $(DEBUG)/* *.a
