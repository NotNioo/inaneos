# boot asm
.section .multiboot, "a"
.align 4
.long 0x1BADB002    # magic
.long 0x00000003    # flags: want mem info from bootloader
.long -(0x1BADB002 + 0x00000003)    # checksum, must sum to zero

.section .bss
.align 16
stack_bottom:
.skip 16384 # 16k stack
stack_top:

.section .text
.global _start
_start:
    cli
    mov $stack_top, %esp
    push %ebx
    push %eax
    call kernel_main
    add $8, %esp
1:  hlt
    jmp 1b
