#include "timer.h"
#include "ports.h"
#include "screen.h"

#define PIT_FREQUENCY 1193180U  // Can also put this here

volatile unsigned long ticks = 0;  // ← CHANGE to unsigned long

void timer_handler() {
    ticks++;
}

void init_timer() {
    unsigned int divisor = PIT_FREQUENCY / 100;  // 100Hz (10ms)
    
    outb(0x43, 0x36);
    outb(0x40, divisor & 0xFF);
    outb(0x40, (divisor >> 8) & 0xFF);
    
    print("Timer initialized at 100Hz\n");
}

// CHANGE to match timer.h declaration (int ms)
void sleep(int ms) {
    unsigned long start = ticks;
    while (ticks < start + ms) {
        asm volatile ("nop");
    }
}

// CHANGE to match timer.h declaration (unsigned long)
unsigned long get_ticks() {
    return ticks;
}
