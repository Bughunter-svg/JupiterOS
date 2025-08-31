#include "screen.h"
#include "keyboard.h"
#include "string.h"
#include "filesystem.h"
#include "process.h"
#include "timer.h"
#include "interrupts.h"
#include "splash.h"
#include "system.h"
#include "ports.h"
#include <stddef.h>

#define LINE_SIZE 128

void print_memory_info() {
    print("Memory: 64MB total (simulated)\n");
    print("Free: 56MB\n");
    print("Used: 8MB\n");
}

// Simulate interrupts manually for testing
void manual_timer_test() {
    static int ticks = 0;
    ticks++;
    
    if (ticks % 500000 == 0) {
        print("[TICK:");
        print_hex(ticks);
        print("] ");
    }
}

void execute_command(char *input) {
    // Simple argument parsing
    char* args[10];
    int argc = 0;
    int i = 0;
    int in_word = 0;
    
    // Parse input into arguments
    while (input[i] && argc < 10) {
        if (input[i] != ' ') {
            if (!in_word) {
                args[argc++] = &input[i];
                in_word = 1;
            }
        } else {
            input[i] = '\0';
            in_word = 0;
        }
        i++;
    }
    
    // Ensure last argument is terminated
    if (in_word && i < LINE_SIZE) {
        input[i] = '\0';
    }
    
    if (argc == 0) return;

    // Now use args[0] as command, args[1] as first argument, etc.
    if (strcmp(args[0], "help") == 0) {
        print("=============== JUPITER OS HELP ===============\n");
        print("| [FILE]    create, read, delete, ls         |\n");
        print("| [FILE]    append, info, cp, edit           |\n");
        print("| [SYSTEM]  clear, echo, meminfo, ps         |\n");
        print("| [SYSTEM]  run, time, timer, sleep          |\n");
        print("| [INFO]    cpuinfo, osinfo, status, df      |\n");
        print("| [HELP]    help                             |\n");
        print("==============================================\n");
    }
    else if (strcmp(args[0], "clear") == 0) {
        clear_screen();
    }
    else if (strcmp(args[0], "calc") == 0) {
    calculator(argc, args);
    }
    
    else if (strcmp(args[0], "echo") == 0 && argc > 1) {
 	for (int i=1; i<argc; i++){
 		print(args[i]);
 		if (i<argc - 1) print(" ");
 	}
 	print("\n");
     }
    else if (strcmp(args[0], "meminfo") == 0) {
        print_memory_info();
    }
    else if (strncmp(args[0], "create", 6) == 0 && argc > 2) {
        fs_create(args[1], args[2]);
    }
    else if (strncmp(args[0], "read", 4) == 0 && argc > 1) {
        const char* content = fs_read(args[1]);
        print(content); print("\n");
    }
    else if (strncmp(args[0], "delete", 6) == 0 && argc > 1) {
        fs_delete(args[1]);
    }
    else if (strcmp(args[0], "ls") == 0) {
        fs_list();
    }
    else if (strcmp(args[0], "ps") == 0) {
        list_processes();
    }
    else if (strncmp(args[0], "run", 3) == 0 && argc > 1) {
        create_process(args[1]);
    }
    else if (strcmp(args[0], "time") == 0) {
        print("Uptime: "); print_hex(get_ticks()); print(" ms\n");
    }
    else if (strncmp(args[0], "sleep", 5) == 0 && argc > 1) {
        int ms = 0;
        char* p = args[1];
        while (*p >= '0' && *p <= '9') {
            ms = ms * 10 + (*p - '0');
            p++;
        }
        print("Sleeping for "); print_hex(ms); print(" ms...\n");
        sleep(ms); print("Awake!\n");
    }
    else if (strcmp(args[0], "timer") == 0) {
        print("Timer ticks: "); print_hex(get_ticks()); print("\n");
    }
    else if (strncmp(args[0], "append", 6) == 0 && argc > 2) {
        fs_append(args[1], args[2]);
    }
    else if (strncmp(args[0], "info", 4) == 0 && argc > 1) {
        fs_info(args[1]);
    }
    else if (strncmp(args[0], "cp", 2) == 0 && argc > 2) {
        fs_copy(args[1], args[2]);
    }
    else if (strncmp(args[0], "edit", 4) == 0 && argc > 1) {
        edit_file(args[1]);
    }
    else if (strcmp(args[0], "cpuinfo") == 0) {
        show_cpuinfo();
    }
    else if (strcmp(args[0], "osinfo") == 0) {
        show_osinfo();
    }
    else if (strcmp(args[0], "status") == 0) {
        show_status();
    }
    else if (strcmp(args[0], "df") == 0) {
        show_diskinfo();
    }
    else {
        print("Unknown command: "); print(args[0]); print("\n");
    }
}

void kmain(unsigned int magic, unsigned int *mb_info) {
    (void)mb_info;
    
    static int boot_count = 0;
    boot_count++;
    
    if (magic != 0x2BADB002) {
        print("Error: Not loaded by Multiboot-compliant loader\n");
        return;
    }
    
    disable_interrupts();
    
    char line[LINE_SIZE];
    clear_screen();
    
    // 🎨 ADD BOOT ANIMATION BEFORE SPLASH
    show_boot_animation();  // ← NEW ANIMATION
    show_splash();          // ← EXISTING SPLASH
    
    print("Boot #"); print_hex(boot_count); print("\n");
    print("Welcome to JupiterOS Shell!\n");
    print("Interrupts: DISABLED (Safe Mode)\n");
    
    fs_init();
    init_scheduler();
    init_interrupts();
    init_timer();

    print("System ready\n");

    while(1) {
        manual_timer_test();
        print("> ");
        get_line(line, LINE_SIZE);
        if (line[0]==0) continue;
        execute_command(line);
    }
}
