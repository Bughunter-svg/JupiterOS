#include "interrupts.h"
#include "ports.h"  // ← ADD THIS LINE for outb function
#include "screen.h"

// IDT entry structure
struct idt_entry {
    unsigned short base_lo;
    unsigned short sel;
    unsigned char always0;
    unsigned char flags;
    unsigned short base_hi;
} __attribute__((packed));

struct idt_ptr {
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

struct idt_entry idt[256];
struct idt_ptr idtp;

extern void isr_timer();

void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags) {
    idt[num].base_lo = (base & 0xFFFF);
    idt[num].base_hi = (base >> 16) & 0xFFFF;
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

void init_idt() {
    idtp.limit = (sizeof(struct idt_entry) * 256) - 1;
    idtp.base = (unsigned int)&idt;
    
    // Clear ALL interrupts first
    for (int i = 0; i < 256; i++) {
        idt_set_gate(i, 0, 0, 0);
    }
    
    // Set up ONLY timer interrupt (IRQ0 -> INT 0x20)
    idt_set_gate(0x20, (unsigned long)isr_timer, 0x08, 0x8E);
    
    asm volatile("lidtl (%0)" : : "r"(&idtp));
}

void init_interrupts() {
    init_idt();
    
    // REMAP PIC - USE outb INSTEAD OF port_byte_out
    outb(0x20, 0x11); outb(0xA0, 0x11);  // ICW1: initialization
    outb(0x21, 0x20); outb(0xA1, 0x28);  // ICW2: map IRQ0-7 to 0x20-27, IRQ8-15 to 0x28-2F
    outb(0x21, 0x04); outb(0xA1, 0x02);  // ICW3: master/slave wiring
    outb(0x21, 0x01); outb(0xA1, 0x01);  // ICW4: 8086 mode
    
    // MASK ALL INTERRUPTS except timer (IRQ0)
    outb(0x21, 0xFE);  // 11111110 - only IRQ0 enabled
    outb(0xA1, 0xFF);  // 11111111 - all slave IRQs disabled
    
    print("PIC remapped - ONLY timer enabled\n");
}

void enable_interrupts() { asm volatile("sti"); }
void disable_interrupts() { asm volatile("cli"); }

void debug_interrupts() {
    print("Interrupt Debug:\n");
    print("IDT Base: "); print_hex((unsigned int)&idt); print("\n");
    print("PIC Mask: "); print_hex(inb(0x21)); print("\n");
}
