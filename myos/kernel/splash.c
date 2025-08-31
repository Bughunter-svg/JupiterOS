#include "splash.h"
#include "screen.h"
#include "timer.h"

void show_boot_animation() {
    clear_screen();
    
    const char* frames[] = {
        "JUPITER OS BOOTING   ",
        "JUPITER OS BOOTING.  ",
        "JUPITER OS BOOTING.. ",
        "JUPITER OS BOOTING..."
    };
    
    // Slower animation - visible timing
    for (int i = 0; i < 20; i++) {  // 3 cycles through all frames
        print_at(frames[i % 4], 30, 12);
        
        // MUCH longer delay - adjust based on your CPU speed
        for (volatile long j = 0; j < 7000000; j++) {
            asm volatile ("nop");
        }
    }
}

void show_splash() {
    clear_screen();  // Clear after animation
    print("############################################\n");
    print("#                                          #\n");
    print("#             JUPITER OS v1.0             #\n");
    print("#                                          #\n");
    print("#        Cosmic Scale Computing           #\n");
    print("#         Built from the Metal Up         #\n");
    print("#                                          #\n");
    print("############################################\n");
}
