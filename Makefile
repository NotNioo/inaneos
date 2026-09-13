CROSS := $(shell command -v i686-elf-gcc 2>/dev/null)
ifeq ($(CROSS),)
CC := gcc
M32 := -m32
else
CC := i686-elf-gcc
M32 :=
endif

CFLAGS := $(M32) -ffreestanding -fno-pic -fno-pie -fno-stack-protector -Wall -Wextra
LD := $(CC)
LDFLAGS := $(M32) -nostdlib -no-pie -Wl,--no-warn-rwx-segments -T linker.ld

OBJS := boot.o kernel.o vga.o keyboard.o io.o

all: kernel.el
kernel.o: io.h vga.h
vga.o: io.h vga.h
keyboard.o: io.h keyboard.h
io.o: io.h

kernel.elf: $(OBJS) linker.ld
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.S
	$(CC) $(CFLAGS) -c -o $@ $<

run: kernel.elf
	qemu-system-i386 -kernel kernel.elf

clean:
	rm -f $(OBJS) kernel.elf

.PHONY: all run clean
