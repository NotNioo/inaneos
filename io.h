// io.h - port in/out helpers

#pragma once

/// Sends one byte data into x86_64 I/O port cpu
extern void outb(unsigned short port, unsigned char val);

/// Receives one byte data from x86_64 I/O port cpu
extern unsigned char inb(unsigned short port);

// Enable interrupts
extern void sti(void);
/// Disable interrupts
extern void cli(void);

/// Waits briefly for an I/O operation to complete.
extern void io_wait(void);
