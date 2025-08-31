#include "keyboard.h"
#include "screen.h"
#include "ports.h"
#include <stdint.h>

#define DATA_PORT 0x60
#define STATUS_PORT 0x64

#define HISTORY_SIZE 10

// --- Scancode map ---
static const char scancode_map[] = {
    0,0,'1','2','3','4','5','6','7','8','9','0','-','=','\b', // Backspace is 14th position
    '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',
    0,'a','s','d','f','g','h','j','k','l',';','\'','`',0,
    '\\','z','x','c','v','b','n','m',',','.','/',0,'*',0,' ',0
};

// --- Shifted scancode map ---
static const char shifted_scancode_map[] = {
    0,0,'!','@','#','$','%','^','&','*','(',')','_','+','\b',
    '\t','Q','W','E','R','T','Y','U','I','O','P','{','}','\n',
    0,'A','S','D','F','G','H','J','K','L',':','"','~',0,
    '|','Z','X','C','V','B','N','M','<','>','?',0,'*',0,' ',0
};

// --- Keyboard history ---
static char history[HISTORY_SIZE][128];
static int history_count = 0;

// --- Shift key tracking ---
static int shift_pressed = 0;

int get_key() {
    uint8_t scancode;

    // Wait for key press
    while (!(inb(STATUS_PORT) & 0x01));
    scancode = inb(DATA_PORT);

    // Handle Shift press/release
    if (scancode == 0x2A || scancode == 0x36) { shift_pressed = 1; return 0; }
    if (scancode == 0xAA || scancode == 0xB6) { shift_pressed = 0; return 0; }

    if (scancode & 0x80) return 0; // ignore key release

    // Handle extended codes (arrows only) - must check for 0xE0 first
    if (scancode == 0xE0) {
        while (!(inb(STATUS_PORT) & 0x01));
        uint8_t ext_scancode = inb(DATA_PORT);
        
        // Only return arrow keys if they're press events (not release)
        if (!(ext_scancode & 0x80)) {
            switch(ext_scancode) {
                case 0x48: return KEY_UP;
                case 0x50: return KEY_DOWN;
                case 0x4B: return KEY_LEFT;
                case 0x4D: return KEY_RIGHT;
            }
        }
        return 0; // ignore other extended codes
    }

    // Map normal scancode - use appropriate map based on shift state
    if (scancode < sizeof(scancode_map)) {
        if (shift_pressed) {
            return shifted_scancode_map[scancode];
        } else {
            return scancode_map[scancode];
        }
    }

    return 0;
}

void get_line(char* buffer, int size) {
    int i = 0;
    int c;
    int temp_index = history_count;

    while (1) {
        c = get_key();
        if (!c) continue;

        if (c == '\r' || c == '\n') { // Enter
            buffer[i] = 0;
            print("\n");
            if (i > 0) {
                // Save to history
                if (history_count < HISTORY_SIZE) history_count++;
                int idx = (history_count - 1) % HISTORY_SIZE;
                int j;
                for (j = 0; j < i; j++) history[idx][j] = buffer[j];
                history[idx][i] = 0;
            }
            temp_index = history_count;
            break;
        } 
        else if (c == '\b') { // Backspace - FIXED
            if (i > 0) { 
                i--; 
                print_char('\b'); // Move back
                print_char(' ');  // Erase character
                print_char('\b'); // Move back again
            }
        }
        else if (c == KEY_UP) {
            if (history_count == 0) continue;
            temp_index--;
            if (temp_index < 0) temp_index = 0;
            // erase current line
            while (i > 0) { print_char('\b'); print_char(' '); print_char('\b'); i--; }
            // copy history
            int j = 0;
            while (history[temp_index][j] && j < size - 1) { buffer[j] = history[temp_index][j]; print_char(buffer[j]); j++; }
            i = j;
        }
        else if (c == KEY_DOWN) {
            if (history_count == 0) continue;
            temp_index++;
            if (temp_index >= history_count) { 
                // Clear line if at the end of history
                while (i > 0) { print_char('\b'); print_char(' '); print_char('\b'); i--; }
                temp_index = history_count;
                continue; 
            }
            // erase current line
            while (i > 0) { print_char('\b'); print_char(' '); print_char('\b'); i--; }
            // copy history
            int j = 0;
            while (history[temp_index][j] && j < size - 1) { buffer[j] = history[temp_index][j]; print_char(buffer[j]); j++; }
            i = j;
        }
        else if (i < size - 1 && c >= 32 && c <= 126) { // Printable ASCII
            buffer[i++] = (char)c;
            print_char((char)c);
        }
    }
}

void get_init() {
    history_count = 0;
    shift_pressed = 0;
}

// Add this function to keyboard.c
void keyboard_handler() {
    // Basic keyboard interrupt handler
    unsigned char scancode = inb(0x60);
    (void)scancode; // Silence unused warning for now
    // Add proper keyboard handling later
}
