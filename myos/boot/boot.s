section .multiboot
align 4
    dd 0x1BADB002              ; magic number
    dd 0x00000003              ; flags
    dd -(0x1BADB002 + 0x00000003) ; checksum

section .text
global _start
extern kmain

_start:
    mov esp, stack_top
    push ebx                   ; multiboot info
    push eax                   ; multiboot magic
    call kmain

.hang:
    hlt
    jmp .hang

section .bss
align 16
stack_bottom:
    resb 16384
stack_top:
