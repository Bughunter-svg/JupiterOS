#include "memory.h"
#include "screen.h"

void* kmalloc(unsigned int size) {  // Change to unsigned int
    print("Allocated ");
    print_hex(size);
    print(" bytes\n");
    return (void*)0x100000;  // Simulated allocation
}

void kfree(void* ptr) {
    (void)ptr;  // Silence unused parameter warning
    print("Freed memory\n");
}
