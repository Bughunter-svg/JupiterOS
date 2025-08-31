#ifndef MEMORY_H
#define MEMORY_H

// Use unsigned int instead of size_t since we can't use stddef.h
void* kmalloc(unsigned int size);
void kfree(void* ptr);

#endif
