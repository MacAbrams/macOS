ARCH=/home/mac/opt/cross/bin/i686-elf
CC=${ARCH}-gcc
LD=${ARCH}-ld
AS=${ARCH}-as
AR=${ARCH}-ar

LIBDIR=../libc
INCLUDEDIR=../include
LIBINCLUDEDIR=$(LIBDIR)/include


CFLAGS:=$(CFLAGS) -O0 -ffreestanding -Wall -Wextra  -g -m32 -I../kernel/include -Iinclude
LDFLAGS:=$(LDFLAGS)
LIBS:=$(LIBS) -nostdlib -lk -lgcc

FREEOBJS=\
string/strlen.o \
string/memcmp.o \
string/memcpy.o \
string/memset.o \
string/memmove.o \
stdio/putchar.o \
stdio/puts.o \
stdio/printf.o \
stdlib/abort.o \

LIBK_OBJS=$(FREEOBJS:.o=.libk.o)

BINARIES=libk.a

.PHONY: all
.SUFFIXES: .o .libk.o .c .S

all: $(BINARIES)
libk.a: $(LIBK_OBJS)
	$(AR) rcs $@ $(LIBK_OBJS)
	#ranlib libtty.a

.c.o:
	$(CC) $(CFLAGS) -c -D_STATIC_LIB=1 $< -o $@
.c.libk.o:
	$(CC) $(CFLAGS) -c -D_STATIC_LIB=1 $< -o $@

clean:
	rm -f $(BINARIES) *.a
	rm -f $(OBJS) $(LIBK_OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) $(LIBK_OBJS:.o=.d) *.d */*.d */*/*.d


-include $(OBJS:.o=.d)
-include $(LIBK_OBJS:.o=.d)
