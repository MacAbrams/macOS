#!/bin/bash
qemu-system-i386 -drive file=everything.bin,format=raw -S -s &
gdb -q -ex="set architecture i686" -ex="target remote :1234" -ex="add-symbol-file dbg/kernel.c.debug" -ex="add-symbol-file dbg/kernel.asm.debug" -ex="add-symbol-file dbg/tty.debug"
