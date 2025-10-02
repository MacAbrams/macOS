#!/bin/bash
qemu-system-i386 -drive file=kernel/everything.bin,format=raw -S -s &
gdb -q -ex="set architecture i686" -ex="target remote :1234" -ex="add-symbol-file dbg/kernel.debug" 
