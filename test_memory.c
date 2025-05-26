struct test {
    int x;
    char y;
} test1;

int main() {
    // Buffer overflow
    int arr[5];
    arr[5] = 10;  // This is out of bounds

    // Use after free scenario
    int *ptr = (int*)malloc(sizeof(int));
    *ptr = 42;
    free(ptr);
    *ptr = 43;    // Use after free

    // Stack buffer overflow
    char str[5];
    strcpy(str, "Hello World");  // Buffer overflow

    return 0;
} 