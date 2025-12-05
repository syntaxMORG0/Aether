#!bin/bash

make clean
make
qemu-system-arm -M versatilepb -m 128M -nographic -kernel build/kernel.img
