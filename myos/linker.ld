ENTRY(_start)

SECTIONS
{
    . = 0x100000;

    .text : ALIGN(4K)
    {
        *(.multiboot)   /* MULTIBOOT HEADER FIRST! */
        *(.text)
    }

    .rodata : ALIGN(4K)
    {
        *(.rodata)
    }

    .data : ALIGN(4K)
    {
        *(.data)
    }

    .bss : ALIGN(4K)
    {
        *(COMMON)
        *(.bss)
    }

    /DISCARD/ : {
        *(.note*)
        *(.iplt*)
        *(.igot*)
        *(.rel*)
        *(.comment)
    }
}
