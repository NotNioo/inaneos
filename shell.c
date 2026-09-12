#include "shell.h"
#include "vga.h"
#include "keyboard.h"
#include "io.h"

static int same(const char *a, const char *b) {
    while (*a && *a == *b) { a++; b++; }
    return *a == *b;
}

static int start_with(const char *s, const char *pre) {
    while (*pre)
        if (*s++ != *pre++) return 0;
    return 1;
}

static void run(const char *line) {
    if (line[0] == '\0') return;

    if (same(line, "help")) {
        term_puts("command available:\n");
        term_puts(" help    //command list\n");
        term_puts(" echo    //print teks\n");
        term_puts(" clear   //clean shell\n");
        term_puts(" info    //about this os\n");
        term_puts(" reboot  //restart\n");
    } else if (start_with(line, "echo")) {
        term_puts(line + 5);
        term_puts("\n");
    } else if (same(line, "clear")) {
        term_clear();
    } else if (same(line, "info")) {
        term_puts("inaneos bv-0.01");
    } else if (same(line, "reboot")) {
        outb(0x64, 0xFF);
        for (;;) __asm__ volatile("hlt");
    } else {
        term_puts(line)l;
        term_puts("could not find the command\n")
    }
}
