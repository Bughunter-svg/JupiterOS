#include "system.h"
#include "screen.h"
#include "string.h"

void show_cpuinfo() {
    print("CPU: i386-compatible\n");
    print("Architecture: 32-bit x86\n");
    print("FPU: Present\n");
    print("Vendor: JupiterOS Virtual CPU\n");
}

void show_meminfo() {
    print("Memory Total: 64MB\n");
    print("Memory Used: 8MB\n");
    print("Memory Free: 56MB\n");
    print("Kernel Size: 2MB\n");
    print("Heap Available: 32MB\n");
}

void show_osinfo() {
    print("JupiterOS v1.0 Alpha\n");
    print("Build Date: " __DATE__ "\n");
    print("Features: Filesystem, Memory Mgmt, Processes\n");
    print("Shell: JupiterSH v1.0\n");
}

void show_status() {
    print("System Status: ONLINE\n");
    print("Uptime: ");
    // Would show actual uptime when interrupts work
    print("0 seconds\n");
    print("Processes: 1 running\n");
    print("Files: 0 open\n");
}

void show_diskinfo() {
    print("Disk: RAM Filesystem\n");
    print("Total Space: 1MB\n");
    print("Used Space: 0.1MB\n");
    print("Free Space: 0.9MB\n");
    print("Files: 0\n");
}

void calculator(int argc, char* args[]) {
    if (argc != 4) {
        print("Usage: calc <number1> <operator> <number2>\n");
        print("Operators: + - * /\n");
        return;
    }
    
    int num1 = atoi_simple(args[1]);
    char op = args[2][0];  // First character of operator
    int num2 = atoi_simple(args[3]);
    int result = 0;
    
    switch (op) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            if (num2 != 0) {
                result = num1 / num2;
            } else {
                print("Error: Division by zero!\n");
                return;
            }
            break;
        default:
            print("Error: Invalid operator. Use + - * /\n");
            return;
    }
    
    print("Result: ");
    print_int(result);
    print("\n");
}
