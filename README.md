# Lexical Analyzer and Parser with Memory Management

A C-based lexical analyzer and parser implementation with custom memory management. This project provides detailed symbol table tracking, constant table management, and a visual abstract syntax tree (AST) representation.

## Features

- **Lexical Analysis**: Tokenizes C code using Flex
- **Parsing**: Generates AST using Yacc/Bison
- **Symbol Table Management**: Tracks identifiers, types, scopes, and line numbers
- **Constant Table**: Manages string and numeric constants
- **Custom Memory Management**: Efficient memory pool with reference counting
- **Beautiful Output Format**: Well-formatted tables and tree visualization

## Build Instructions

```bash
make clean   # Clean previous build
make        # Build the compiler
```

## Usage

1. Create your C source file (e.g., test1.c)
2. Run the compiler:
```bash
./compiler
```

## Output Format

The compiler generates three main sections of output:

### 1. Symbol Table
```
┌────────────┬──────────┬──────────┬───────────┬──────────┐
│ SYMBOL     │ TYPE     │ CLASS    │ SCOPE     │ LINE     │
├────────────┼──────────┼──────────┼───────────┼──────────┤
│ ...        │ ...      │ ...      │ ...       │ ...      │
└────────────┴──────────┴──────────┴───────────┴──────────┘
```

### 2. Constant Table
```
┌────────────────────────┬────────────────────────┐
│ CONSTANT               │ TYPE                   │
├────────────────────────┼────────────────────────┤
│ ...                    │ ...                    │
└────────────────────────┴────────────────────────┘
```

### 3. Abstract Syntax Tree
```
├── root
│   ├── child1
│   │   ├── subchild1
│   │   └── subchild2
│   └── child2
        └── subchild3
```

### 4. Memory Statistics
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

## Memory Management

The project uses a custom memory management system with the following features:
- Memory pool allocation
- Reference counting
- Automatic cleanup
- Memory usage tracking
- Peak memory monitoring

## Files

- `final_lexer.l`: Flex lexical analyzer definition
- `final_parser.y`: Yacc/Bison parser definition
- `custom_memory.c`: Memory management implementation
- `custom_memory.h`: Memory management header
- `Makefile`: Build configuration

## Error Handling

The compiler provides clear error messages for:
- Syntax errors
- Memory allocation failures
- Invalid token errors
- Parse errors

## Dependencies

- Flex (for lexical analysis)
- Bison (for parsing)
- GCC (for compilation)
- Make (for build automation)

## License

This project is open source and available under the MIT License.
