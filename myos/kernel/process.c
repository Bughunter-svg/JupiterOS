#include "process.h"
#include "screen.h"
#include "string.h"  // ADD THIS FOR strcpy
#include "string.h"  // ADD THIS FOR print_hex

#define MAX_PROCESSES 10
process_t processes[MAX_PROCESSES];
int current_pid = 0;
int process_count = 0;

void init_scheduler() {
    for (int i = 0; i < MAX_PROCESSES; i++) {
        processes[i].state = 0; // EMPTY
    }
    print("Scheduler initialized\n");
}

// Remove the unused function parameter for now
int create_process(char* name) {  // REMOVE the function parameter
    for (int i = 0; i < MAX_PROCESSES; i++) {
        if (processes[i].state == 0) {
            processes[i].pid = i;
            strcpy(processes[i].name, name);
            processes[i].state = 1; // READY
            process_count++;
            
            print("Created process: ");
            print(name);
            print("\n");
            return i;
        }
    }
    return -1;
}

void list_processes() {
    print("Running processes:\n");
    for (int i = 0; i < MAX_PROCESSES; i++) {
        if (processes[i].state != 0) {
            print("  PID ");
            print_hex(i);  // Now print_hex is available
            print(": ");
            print(processes[i].name);
            print("\n");
        }
    }
}
