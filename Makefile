CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
AS = arm-none-eabi-as
OBJCOPY = arm-none-eabi-objcopy
CFLAGS = -Wall -O2 -ffreestanding -nostdlib -nostartfiles
LDFLAGS = -T src/linker.ld

ELF = build/kernel.elf
IMG = build/kernel.img

OBJ = build/boot.o build/kernel.o build/io.o

all: build build/kernel.img

build:
	mkdir -p build

build/%.o: src/%.s
	$(AS) $< -o $@

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(ELF): $(OBJ)
	$(LD) $(LDFLAGS) $^ -o $@

$(IMG): $(ELF)
	$(OBJCOPY) -O binary $< $@

run: $(IMG)
	@qemu-system-arm -M versatilepb -m 128M -nographic -kernel $<

r: run

clean:
	rm -rf ./build/
