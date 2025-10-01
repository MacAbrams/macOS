ARCH=/home/mac/opt/cross/bin/i686-elf
CC=${ARCH}-gcc
LD=${ARCH}-ld
AS=${ARCH}-as
AR=${ARCH}-ar

INCLUDEDIR=./include/


CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra  -g -m32 -I$(INCLUDEDIR)
LDFLAGS:=$(LDFLAGS)
LIBS:=$(LIBS) -nostdlib -lk -lgcc

FREEOBJS=\
$(ARCH_FREEOBJS) \


LIBK_OBJS=$(FREEOBJS:.o=.libk.o)

LINK_LIST=\
kernel.c\

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
	$(LD) $(LDFLAGS) -Ttext 0x1000 kernel.asm.o kernel.c.o tty.o --oformat binary -g -o kernel.bin
	cat "boot.bin" "kernel.bin" "zero"> everything.bin
	objcopy kernel.asm.o dbg/kernel.asm.debug
	objcopy kernel.c.o dbg/kernel.c.debug
libs:
	cp tty.h $(INCLUDEDIR)
	$(CC) $(CFLAGS) -c -D_STATIC_LIB=1 tty.c -o tty.o
	$(AR) r libtty.a tty.o
	ranlib libtty.a
