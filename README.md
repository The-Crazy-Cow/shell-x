# shell-x

Minimal Unix-like shell written in C.

## Current status

The project currently provides:

- a REPL loop for the shell;
- configurable prompt management;
- shell execution status management (`RUNNING` / `STOPPED`);
- a basic command parser placeholder;
- CMake-based builds and recursive `clang-format` support.

User input reading and command execution are still under development.

## Build

Requirements: a C compiler, CMake, and GNU Make.

```bash
cmake -S . -B build
cmake --build build
```

Run the shell:

```bash
./build/src/shell-x
```

## Formatting

Format all project C and header files with the repository `.clang-format` file:

```bash
cmake --build build --target format
```

## Project layout

```text
include/        Public headers and debug implementation
src/            Program entry point and shell core
src/core/cli/   Prompt and command-line parser
utils/          Utility code
```