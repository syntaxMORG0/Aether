CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
AS = arm-none-eabi-as
OBJCOPY = arm-none-eabi-objcopy
CFLAGS = -Wall -O2 -ffreestanding -nostdlib -nostartfiles
LDFLAGS = -T src/linker.ld

all: build build/kernel.img

build:
	mkdir -p build

build/boot.o: src/boot.s
	$(AS) $< -o $@

build/kernel.o: src/kernel.c
	$(CC) $(CFLAGS) -c $< -o $@

build/kernel.elf: build/boot.o build/kernel.o
	$(LD) $(LDFLAGS) build/boot.o build/kernel.o -o build/kernel.elf

build/kernel.img: build/kernel.elf
	$(OBJCOPY) -O binary build/kernel.elf build/kernel.img

run: build/kernel.img
	qemu-system-arm -M versatilepb -m 128M -nographic -kernel build/kernel.img

clean:
	rm -rf ./build/
