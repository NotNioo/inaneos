CFLAGS = -m32 -ffreestanding -fno-stack-protector -fno-pic -fno-pie -02 -Wall

all: os.iso

kernel.elf: kernel.o vga.o keyboard.o shell.o

%.o: %.c io.h vga.h idt.h keyboard.h shell.h
    gcc $(CFLAGS) -c $< $@

os.iso: kernel.elf
    mkdir -p isodir/boot/grub
    cp kernel.elf isodir/boot/
    cp grub.cfg isodir/boot/grub/grub.cfg
    grub-mkrescue -o os.iso isodir

run: os.iso
    qemu-system-i386 -cdrom os.iso

clean:
    rm -rf *.o kernel.elf os.iso
