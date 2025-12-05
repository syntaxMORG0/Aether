#!bin/bash

make clean
make
clear
qemu-system-arm -M versatilepb -m 128M -nographic -kernel build/kernel.img
