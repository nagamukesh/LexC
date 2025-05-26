#ifndef CUSTOM_MEMORY_H
#define CUSTOM_MEMORY_H

#include <stddef.h>

void init_memory_pool(size_t size);
void* custom_malloc(size_t size);
void increment_ref(void* ptr);
void decrement_ref(void* ptr);
void custom_free(void* ptr);
void assign(void** dest, void* src);
void free_memory_pool(void);

#endif