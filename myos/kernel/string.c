#include "string.h"
#include "screen.h"
#include <stddef.h>

// ==== ESSENTIAL STRING FUNCTIONS (MISSING!) ====
int strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

int strlen(const char *str) {
    int len = 0;
    while (str[len]) len++;
    return len;
}

void strcpy(char *dest, const char *src) {
    while (*src) {
        *dest++ = *src++;
    }
    *dest = '\0';
}

int strncmp(const char *s1, const char *s2, int n) {
    while (n && *s1 && (*s1 == *s2)) {
        s1++;
        s2++;
        n--;
    }
    if (n == 0) return 0;
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

// ==== YOUR EXISTING UTILITY FUNCTIONS ====
void print_hex(unsigned int n) {
    char hex_chars[] = "0123456789ABCDEF";
    char hex[9];
    hex[8] = 0;
    
    for (int i = 7; i >= 0; i--) {
        hex[i] = hex_chars[n & 0xF];
        n >>= 4;
    }
    print("0x");
    print(hex);
}

void print_int(int n) {
    char buffer[16];
    itoa(n, buffer, 10);
    print(buffer);
}

void itoa(int num, char *buffer, int base) {
    int i = 0;
    int is_negative = 0;
    
    if (num == 0) {
        buffer[i++] = '0';
        buffer[i] = '\0';
        return;
    }
    
    if (num < 0 && base == 10) {
        is_negative = 1;
        num = -num;
    }
    
    while (num != 0) {
        int rem = num % base;
        buffer[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }
    
    if (is_negative) {
        buffer[i++] = '-';
    }
    
    buffer[i] = '\0';
    reverse(buffer);
}

void reverse(char *str) {
    int length = strlen(str);
    for (int i = 0; i < length / 2; i++) {
        char temp = str[i];
        str[i] = str[length - i - 1];
        str[length - i - 1] = temp;
    }
}

int atoi_simple(const char* str) {
    int result = 0;
    int sign = 1;
    int i = 0;
    
    if (str[0] == '-') {
        sign = -1;
        i++;
    }
    
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    
    return sign * result;
}
