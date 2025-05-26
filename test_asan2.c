#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    printf("\n=== Running ASan Tests ===\n\n");

    // Test 1: Buffer Overflow
    // printf("Test 1: Buffer Overflow\n");
    // char *array = malloc(10);
    // strcpy(array, "This string is too long for the buffer");
    // free(array);

    // Test 2: Use after free
    printf("Test 2: Use after free\n");
    int *ptr = malloc(sizeof(int));
    *ptr = 42;
    free(ptr);
    *ptr = 100;  // Use after free

    // Test 3: Memory leak
    printf("\nTest 3: Memory leak\n");
    int *leak = malloc(sizeof(int));
    *leak = 42;
    // Deliberately not freeing to cause leak

    return 0;
} 