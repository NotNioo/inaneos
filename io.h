
#pragma once
#include <stdint.h>

static inline void outb(unsigned short port, unsigned char val) {
  __asm__ volatile("outb %0, %1" ::"a"(val), "Nd"(port));
}

static inline unsigned char inb(unsigned short port) {
  unsigned char ret;
  __asm__ volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
  return ret;
}

static inline void sti() { __asm__ volatile("sti"); }
static inline void cli() { __asm__ volatile("cli"); }

static inline void io_wait() {
  // regardless the value
  // it will create a tiny delay to wait
  // the io work to be finished
  __asm__ volatile("outb %%al, $0x80" : : "a"(0));
}