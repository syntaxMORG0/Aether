CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
AS = arm-none-eabi-as
OBJCOPY = arm-none-eabi-objcopy
CFLAGS = -Wall -O2 -ffreestanding -nostdlib -nostartfiles
LDFLAGS = -T linker.ld

all: kernel.img

boot.o: boot.S
	$(AS) boot.S -o boot.o

kernel.o: kernel.c
	$(CC) $(CFLAGS) -c kernel.c -o kernel.o

kernel.elf: boot.o kernel.o linker.ld
	$(LD) $(LDFLAGS) boot.o kernel.o -o kernel.elf

kernel.img: kernel.elf
	$(OBJCOPY) -O binary kernel.elf kernel.img

run: kernel.img
	qemu-system-arm -M versatilepb -m 128M -nographic -kernel kernel.img

clean:
	rm -f *.o *.elf *.img
