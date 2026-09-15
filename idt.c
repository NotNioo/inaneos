#include "idt.h"
#include "keyboard.h"
#include "vga.h"
#include "io.h"

struct gate {
    unsigned short offset_low;
    unsigned short selector;
    unsigned char zero;
    unsigned char type_attr;
    unsigned short offset_high;
} __attribute__((packed));

static struct gate idt[256];

void idt_set_gate(int n, unsigned int handler) {
    idt[n].offset_low = handler & 0xFFFF;
    idt[n].selector    = 0x08;      // segment kode milik GRUB
    idt[n].zero        = 0;
    idt[n].type_attr   = 0x8E;
    idt[n].offset_high = (handler >> 16) & 0xFFFF;
}

// Dipanggil jika CPU mengalami exception (page fault, divide by zero, dll)
void panic(void) {
    term_set_color(0x0C, 0x00);
    term_puts("\n*** EXCEPTION! CPU menemukan kondisi fatal ***\n");
    for (;;) __asm__ volatile("hlt");
}

__attribute__((naked))
void exception_stub(void) {
    __asm__ volatile(
        "pusha\n"
        "call panic\n"
        "1: hlt\n"
        "jmp 1b"
    );
}

void idt_init(void) {
    struct { unsigned short limit; unsigned int base; } __attribute__((packed))
        p = { sizeof(idt) - 1, (unsigned int)idt };

    for (int i = 0; i < 32; i++)
        idt_set_gate(i, (unsigned int)exception_stub);


    idt_set_gate(0x21, (unsigned int)irq1_stub);

    __asm__ volatile("lidt %0" :: "m"(p));
}

void pic_init(void) {
    outb(0x20, 0x11); outb(0xA0, 0x11);
    outb(0x21, 0x20); outb(0xA1, 0x28);
    outb(0x21, 0x04); outb(0xA1, 0x02);
    outb(0x21, 0x01); outb(0xA1, 0x01);
    outb(0x21, 0xFD);
    outb(0xA1, 0xFF);
}
