#!bin/bash

make clean && make && (qemu-system-arm -M versatilepb -m 128M -nographic -kernel kernel.img 2>&1 &) 