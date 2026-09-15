CFLAGS = -m32 -ffreestanding -fno-stack-protector -fno-pic -fno-pie -O2 -Wall -g -MMD -MP

OBJS = boot.o kernel.o vga.o idt.o keyboard.o shell.o

all: os.iso

kernel.elf: $(OBJS) linker.ld
	ld -m elf_i386 -T linker.ld -o $@ $(OBJS)

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

%.o: %.S
	gcc $(CFLAGS) -c $< -o $@

os.iso: kernel.elf grub.cfg
	mkdir -p isodir/boot/grub
	cp kernel.elf isodir/boot/
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o os.iso isodir

run: os.iso
	qemu-system-i386 -cdrom os.iso

clean:
	rm -f *.o kernel.elf os.iso
	rm -rf isodir

.PHONY: all run clean

-include $(OBJS:.o=.d)
