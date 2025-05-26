// custom_memory.c

#include "custom_memory.h"
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MEMORY_POOL_SIZE (64 * 1024) // 64KB
#define ALIGNMENT 8 // Align to 8-byte boundaries

// Statistics tracking
static size_t total_allocations = 0;
static size_t total_frees = 0;
static size_t current_allocated_bytes = 0;
static size_t peak_allocated_bytes = 0;

// Metadata stored at the beginning of each allocated block
typedef struct BlockHeader {
    size_t size;          // Size of the user data
    int ref_count;        // Reference count
    struct BlockHeader* next_free; // Pointer to next free block (used when in free list)
} BlockHeader;

static void* memory_pool = NULL;
static size_t memory_pool_size = 0;
static BlockHeader* free_list = NULL;
static BlockHeader* allocated_blocks = NULL;

// Function to print memory statistics
void print_memory_stats() {
    printf("\n╔════════════════════════════════════╗");
    printf("\n║      Memory Pool Statistics        ║");
    printf("\n╠════════════════════════════════════╣");
    printf("\n║ Total allocations: %-14zu ║", total_allocations);
    printf("\n║ Total frees: %-19zu ║", total_frees);
    printf("\n║ Peak memory used: %-15zu ║", peak_allocated_bytes);
    printf("\n║ Memory pool size: %-14zu ║", memory_pool_size);
    printf("\n╚════════════════════════════════════╝\n");
}

// Returns the total size needed for a block including its header
static size_t total_size(size_t user_size) {
    return ((sizeof(BlockHeader) + user_size + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1));
}

// Returns a pointer to user data from a block header
static void* block_to_ptr(BlockHeader* block) {
    return (void*)((char*)block + sizeof(BlockHeader));
}

// Returns a pointer to block header from user data
static BlockHeader* ptr_to_block(void* ptr) {
    return (BlockHeader*)((char*)ptr - sizeof(BlockHeader));
}

// Function to initialize the memory pool
void init_memory_pool(size_t size) {
    if (memory_pool == NULL) {
        memory_pool = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        if (memory_pool == MAP_FAILED) {
            perror("mmap");
            memory_pool = NULL;
        } else {
            memory_pool_size = size;
            memset(memory_pool, 0, size);
            
            // Initialize free list with the entire pool
            free_list = (BlockHeader*)memory_pool;
            free_list->size = size - sizeof(BlockHeader);
            free_list->ref_count = 0;
            free_list->next_free = NULL;
        }
    }
}

// Function to allocate memory from the pool
void* custom_malloc(size_t size) {
    if (size == 0 || memory_pool == NULL) {
        return NULL;
    }
    
    size_t block_size = total_size(size);
    BlockHeader** current = &free_list;
    
    while (*current) {
        if ((*current)->size >= block_size) {
            BlockHeader* found_block = *current;
            *current = found_block->next_free;
            
            if (found_block->size >= block_size + sizeof(BlockHeader) + ALIGNMENT) {
                size_t remaining_size = found_block->size - block_size;
                BlockHeader* new_free = (BlockHeader*)((char*)found_block + block_size);
                new_free->size = remaining_size - sizeof(BlockHeader);
                new_free->ref_count = 0;
                new_free->next_free = free_list;
                free_list = new_free;
                found_block->size = block_size - sizeof(BlockHeader);
            }
            
            found_block->ref_count = 1;
            found_block->next_free = (BlockHeader*)allocated_blocks;
            allocated_blocks = found_block;
            
            total_allocations++;
            current_allocated_bytes += found_block->size;
            if (current_allocated_bytes > peak_allocated_bytes) {
                peak_allocated_bytes = current_allocated_bytes;
            }
            
            return block_to_ptr(found_block);
        }
        current = &(*current)->next_free;
    }
    
    return NULL;
}

// Function to increment reference count
void increment_ref(void* ptr) {
    if (ptr == NULL) {
        printf("Cannot increment reference count of NULL pointer\n");
        return;
    }
    
    BlockHeader* block = ptr_to_block(ptr);
    block->ref_count++;
    printf("Incremented ref count for %p to %d\n", ptr, block->ref_count);
}

// Function to decrement reference count and free memory if needed
void decrement_ref(void* ptr) {
    if (ptr == NULL) return;
    
    BlockHeader* block = ptr_to_block(ptr);
    block->ref_count--;
    
    if (block->ref_count <= 0) {
        BlockHeader** current = (BlockHeader**)&allocated_blocks;
        while (*current && *current != block) {
            current = (BlockHeader**)&(*current)->next_free;
        }
        
        if (*current) {
            *current = (BlockHeader*)block->next_free;
        }
        
        block->next_free = free_list;
        free_list = block;
        
        total_frees++;
        current_allocated_bytes -= block->size;
    }
}

// Function to free memory explicitly
void custom_free(void* ptr) {
    if (ptr) {
        decrement_ref(ptr);
    }
}

// Function to assign one pointer to another
void assign(void** dest, void* src) {
    if (dest && *dest) {
        decrement_ref(*dest);
    }
    if (dest) {
        *dest = src;
        if (src) {
            increment_ref(src);
        }
    }
}

// Function to free the entire memory pool
void free_memory_pool(void) {
    if (memory_pool) {
        print_memory_stats();  // Print final statistics
        
        if (munmap(memory_pool, memory_pool_size) == 0) {
            memory_pool = NULL;
            memory_pool_size = 0;
            allocated_blocks = NULL;
            free_list = NULL;
            
            // Reset statistics
            total_allocations = 0;
            total_frees = 0;
            current_allocated_bytes = 0;
            peak_allocated_bytes = 0;
        } else {
            perror("munmap");
        }
    }
} 