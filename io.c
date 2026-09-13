
#include "io.h"

void outb(unsigned short port, unsigned char val) {
    __asm__ volatile("outb %0, %1" :: "a"(val), "Nd"(port));
}

unsigned char inb(unsigned short port)  {
    unsigned char ret;
    __asm__ volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

void sti() { __asm__ volatile("sti"); }
void cli() { __asm__ volatile("cli"); }

void io_wait() {
    // regardless the value
    // it will create a tiny delay to wait 
    // the io work to be finished
    outb(0x80, 0);
}