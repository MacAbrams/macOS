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

ARCHOBJS1=\
gdt.c.o \
idt.c.o \
timer.c.o \
gdt.asm.o \
idt.asm.o \
keys.c.o \

.PHONY: all
.SUFFIXES: .o .libk.o .c .S

all:
	make boot
	make libs
	make arch
	make kernel

boot:
	nasm -fbin boot.asm -o boot.bin
	
kernel:
	nasm -felf kernel.asm -o kernel.asm.o
#	$(CC) $(CFLAGS) -o $@ $(LINK_LIST)
	$(CC) $(CFLAGS) -c kernel.c -o kernel.c.o
#	nasm -felf gdt.asm -o gdt.asm.o
#	nasm -felf idt.asm -o idt.asm.o
#	$(CC) $(CFLAGS) -c gdt.c -o gdt.c.o
#	$(CC) $(CFLAGS) -c idt.c -o idt.c.o
#	$(CC) $(CFLAGS) -c timer.c -o timer.c.o
	$(LD) $(LDFLAGS) -T linker.ld kernel.asm.o kernel.c.o tty.o $(ARCHOBJS1) $(LIBDIR)/libk.a --oformat binary -g -o kernel.bin
	$(LD) $(LDFLAGS) -T linker.ld kernel.asm.o kernel.c.o tty.o $(ARCHOBJS1) $(LIBDIR)/libk.a  -g -o $(DEBUG)/kernel.debug
	#$(LD) $(LDFLAGS) -Ttext 0x1000 kernel.asm.o kernel.c.o tty.o gdt.c.o gdt.asm.o idt.c.o idt.asm.o timer.c.o $(LIBDIR)/libk.a --oformat binary -g -o kernel.bin
	cat "boot.bin" "kernel.bin" "checkFile" "zero"> everything.bin
	objcopy kernel.asm.o $(DEBUG)/kernel.asm.debug
	objcopy kernel.c.o $(DEBUG)/kernel.c.debug
arch:
	OBJS=$$(echo "$(ARCHOBJS1:.c.o=.c)" | sed 's/ /\n/g' | grep .c);for FILE in $$OBJS; do $(CC) $(CFLAGS) -c $$FILE -o "$${FILE}.o"; done
	OBJS=$$(echo "$(ARCHOBJS1:.asm.o=.asm)" | sed 's/ /\n/g' | grep .asm);for FILE in $$OBJS; do nasm -felf $$FILE -o "$${FILE}.o"; done

libs:
	$(CC) $(CFLAGS) -c -D_STATIC_LIB=1 tty.c -o tty.o
	objcopy tty.o $(DEBUG)/tty.debug
	$(AR) r libtty.a tty.o
	ranlib libtty.a

clean:
	rm *.o *.bin $(DEBUG)/* *.a
