# Advanced C Compiler with Custom Memory Management

A sophisticated C compiler implementation featuring lexical analysis, parsing, and custom memory management with comprehensive debugging and sanitization capabilities.

## Core Features

### 1. Compiler Components
- **Lexical Analyzer**: Built with Flex for efficient token recognition
- **Parser**: Implemented using Yacc/Bison for syntax analysis
- **Symbol Table**: Advanced tracking of identifiers, types, scopes, and line numbers
- **Constant Table**: Efficient management of string and numeric constants
- **Abstract Syntax Tree (AST)**: Visual representation of code structure
- **Custom Memory Management**: Pool-based allocation with reference counting

### 2. Memory Management System

#### Architecture
- **Memory Pool**: Pre-allocated memory space for efficient allocation
- **Reference Counting**: Tracks object lifetime and prevents memory leaks
- **Block Headers**: Metadata tracking for each allocated block
- **Free List**: Efficient reuse of freed memory blocks

#### Key Features
- Dynamic memory pool initialization
- Automatic memory cleanup
- Memory usage statistics
- Peak memory tracking
- Reference count management
- Memory leak prevention

### 3. Output Format

#### Symbol Table Display
```
┌────────────┬──────────┬──────────┬───────────┬──────────┐
│ SYMBOL     │ TYPE     │ CLASS    │ SCOPE     │ LINE     │
├────────────┼──────────┼──────────┼───────────┼──────────┤
│ ...        │ ...      │ ...      │ ...       │ ...      │
└────────────┴──────────┴──────────┴───────────┴──────────┘
```

#### Constant Table Display
```
┌────────────────────────┬────────────────────────┐
│ CONSTANT               │ TYPE                   │
├────────────────────────┼────────────────────────┤
│ ...                    │ ...                    │
└────────────────────────┴────────────────────────┘
```

#### Memory Statistics
```
╔════════════════════════════════════╗
║      Memory Pool Statistics        ║
╠════════════════════════════════════╣
║ Total allocations: xxx            ║
║ Total frees: xxx                  ║
║ Peak memory used: xxx             ║
║ Memory pool size: xxx             ║
╚════════════════════════════════════╝
```

## Building and Running

### Standard Build
```bash
make clean   # Clean previous build artifacts
make        # Build the compiler
```

### Debug Builds

1. **Address Sanitizer (ASan)**
```bash
make debug
ASAN_OPTIONS=detect_leaks=1:print_stacktrace=1 ./compiler
```

2. **Memory Leak Check**
```bash
make memcheck
```

3. **Thread Sanitizer**
```bash
make thread
```

4. **Undefined Behavior Detection**
```bash
make undefined
```

## Memory Analysis and Debugging

### Address Sanitizer Features

1. **Memory Error Detection**
   - Buffer overflows (stack, heap, global)
   - Use-after-free
   - Use-after-return
   - Use-after-scope
   - Double-free
   - Memory leaks
   - Initialization issues

2. **How It Works**
   - Instruments memory accesses at compile time
   - Maintains shadow memory to track memory state
   - Checks every memory operation for validity
   - Provides detailed error reports with stack traces

### Example Error Detection

1. **Buffer Overflow**
```c
char *array = malloc(10);
strcpy(array, "This is too long");  // ASan will detect this
```

2. **Use After Free**
```c
int *ptr = malloc(sizeof(int));
free(ptr);
*ptr = 42;  // ASan will detect this
```

3. **Memory Leak**
```c
int *leak = malloc(sizeof(int));
// No free - ASan will report leak
```

### Debugging Output

ASan provides detailed error reports including:
- Error type and location
- Stack trace of the error
- Allocation/deallocation history
- Memory state visualization
- Shadow memory mapping

## Custom Memory Management Details

### Memory Pool
- Pre-allocated large memory block
- Reduces system call overhead
- Enables efficient memory reuse

### Block Structure
```c
struct BlockHeader {
    size_t size;         // Size of the block
    int ref_count;       // Reference counter
    struct BlockHeader *next_free;  // Free list pointer
};
```

### Memory Operations
1. **Allocation**
   - Search free list for suitable block
   - Split blocks if necessary
   - Update metadata and statistics

2. **Deallocation**
   - Decrease reference count
   - Merge adjacent free blocks
   - Add to free list when ref_count = 0

3. **Reference Counting**
   - Track object usage
   - Automatic cleanup when no references remain
   - Prevents memory leaks

## Best Practices

### Memory Management
1. Always initialize the memory pool before use
2. Check allocation return values
3. Properly maintain reference counts
4. Clean up memory pool on program exit

### Debugging
1. Use ASan for development builds
2. Enable stack traces for detailed error reports
3. Monitor memory statistics
4. Regular memory leak checks

## Dependencies

- **Flex**: Lexical analyzer generator
- **Bison**: Parser generator
- **GCC**: C compiler with sanitizer support
- **Make**: Build automation

## License

This project is open source and available under the MIT License.

## Contributing

1. Fork the repository
2. Create a feature branch
3. Submit a pull request
4. Ensure tests pass
5. Update documentation
