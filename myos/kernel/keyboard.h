#ifndef KEYBOARD_H
#define KEYBOARD_H

#define KEY_UP 0x80
#define KEY_DOWN 0x81
#define KEY_LEFT 0x82
#define KEY_RIGHT 0x83

int get_key();
void get_line(char* buffer, int size);
void get_init();

#endif
