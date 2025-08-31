#ifndef PROCESS_H
#define PROCESS_H

typedef struct {
    int pid;
    char name[32];
    void* stack_ptr;
    int state;
} process_t;

void init_scheduler();
int create_process(char* name);  // REMOVE the function parameter
void list_processes();

#endif
