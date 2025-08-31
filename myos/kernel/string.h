#ifndef STRING_H
#define STRING_H

int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, int n);
int strlen(const char *str);
void strcpy(char *dest, const char *src);
void print_hex(unsigned int n);
void print_int(int n);
void itoa(int num, char *buffer, int base);
void reverse(char *str);

#endif
