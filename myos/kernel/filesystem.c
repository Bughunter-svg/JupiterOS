#include "filesystem.h"
#include "screen.h"
#include "string.h"
#include <stddef.h>

typedef struct {
    char name[MAX_FILENAME];
    char data[MAX_FILE_SIZE];
    int size;
    int used;
} file_t;

static file_t files[MAX_FILES];

void fs_init() {
    for (int i = 0; i < MAX_FILES; i++) {
        files[i].used = 0;
    }
    print("File system initialized\n");
}

int fs_create(const char* filename, const char* content) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (!files[i].used) {
            strcpy(files[i].name, filename);
            strcpy(files[i].data, content);
            files[i].size = strlen(content);
            files[i].used = 1;
            
            print("Created file: ");
            print(filename);
            print("\n");
            return 1;
        }
    }
    print("Error: No free file slots\n");
    return 0;
}

const char* fs_read(const char* filename) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (files[i].used && strcmp(files[i].name, filename) == 0) {
            return files[i].data;
        }
    }
    return "Error: File not found";
}

int fs_delete(const char* filename) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (files[i].used && strcmp(files[i].name, filename) == 0) {
            files[i].used = 0;
            print("Deleted file: ");
            print(filename);
            print("\n");
            return 1;
        }
    }
    print("Error: File not found\n");
    return 0;
}

void fs_list() {
    print("Files:\n");
    for (int i = 0; i < MAX_FILES; i++) {
        if (files[i].used) {
            print("  ");
            print(files[i].name);
            print(" (");
            print_hex(files[i].size);
            print(" bytes)\n");
        }
    }
}

void fs_append(const char* filename, const char* content) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (files[i].used && strcmp(files[i].name, filename) == 0) {
            int available_space = MAX_FILE_SIZE - files[i].size;
            int content_len = strlen(content);
            
            if (content_len <= available_space) {
                strcpy(files[i].data + files[i].size, content);
                files[i].size += content_len;
                print("Appended to ");
                print(filename);
                print("\n");
            } else {
                print("Error: Not enough space in file\n");
            }
            return;
        }
    }
    print("Error: File not found\n");
}

void fs_info(const char* filename) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (files[i].used && strcmp(files[i].name, filename) == 0) {
            print("File: ");
            print(filename);
            print("\nSize: ");
            print_hex(files[i].size);
            print(" bytes\n");
            print("Content: \"");
            print(files[i].data);
            print("\"\n");
            return;
        }
    }
    print("Error: File not found\n");
}

void fs_copy(const char* source, const char* dest) {
    const char* content = fs_read(source);
    if (strcmp(content, "Error: File not found") != 0) {
        fs_create(dest, content);
        print("Copied ");
        print(source);
        print(" to ");
        print(dest);
        print("\n");
    } else {
        print("Error: Source file not found\n");
    }
}

int edit_file(const char* filename) {
    print("Edit mode - not fully implemented yet\n");
    print("Use 'create' and 'append' for now\n");
    return 0;
}
