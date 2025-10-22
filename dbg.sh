#!/bin/bash
qemu-system-x86_64 -drive file=kernel/everything.bin,format=raw -S -s &
#gdb -q -ex="set architecture i686" -ex="target remote :1234" -ex="add-symbol-file dbg/kernel.debug" 
gdb -q -ex="target remote :1234" -ex="add-symbol-file dbg/kernel.debug" 
