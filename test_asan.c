#include <stdio.h>
#include <stdlib.h>
#include "custom_memory.h"

void test_buffer_overflow() {
    // Allocate a small buffer
    char* buf = (char*)custom_malloc(5);
    printf("Testing buffer overflow...\n");
    
    // Write beyond buffer bounds
    for (int i = 0; i < 10; i++) {
        buf[i] = 'A';  // Will overflow after i=4
    }
    
    custom_free(buf);
}

void test_use_after_free() {
    // Allocate memory
    int* ptr = (int*)custom_malloc(sizeof(int));
    *ptr = 42;
    
    printf("Testing use after free...\n");
    custom_free(ptr);
    
    // Use after free
    *ptr = 100;  // This should be caught by ASan
}

void test_double_free() {
    printf("Testing double free...\n");
    int* ptr = (int*)custom_malloc(sizeof(int));
    
    custom_free(ptr);
    custom_free(ptr);  // Double free
}

int main() {
    init_memory_pool(1024);  // Initialize with 1KB
    
    printf("\n=== Running Memory Tests ===\n\n");
    
    // Uncomment each test individually to see ASan in action
    test_buffer_overflow();
    // test_use_after_free();
    // test_double_free();
    
    free_memory_pool();
    return 0;
} 