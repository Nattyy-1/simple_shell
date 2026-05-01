# Simple Shell

A custom UNIX command-line interpreter (shell) built from scratch in C, implementing core shell functionality following POSIX standards.

## Overview

This project replicates the behavior of `sh` (the standard UNIX shell) by implementing a minimal but functional command interpreter that reads user input, parses commands, resolves executables, and executes them via system calls.

## Features

- **Interactive & Non-Interactive Modes**: Displays a customizable prompt in interactive mode; reads from stdin in non-interactive mode
- **Command Execution**: Resolves commands via the `PATH` environment variable and executes them using `fork()`/`execve()`
- **Multi-Command Support**: Executes multiple commands separated by `;` in a single line
- **Comment Handling**: Ignores inline and full-line comments (`#`)
- **Built-in Commands**:
  - `exit` — exits the shell with an optional status code
  - `env` — prints the current environment variables
  - `setenv` — creates or updates an environment variable
  - `unsetenv` — removes an environment variable
  - `cd` — changes the working directory (supports `~`, `-`, and absolute/relative paths)
- **Signal Handling**: Gracefully handles `SIGINT` (Ctrl+C) and EOF (Ctrl+D)
- **Manual PATH Lookup**: Parses and searches `PATH` directories to locate executables
- **Memory Safety**: Proper allocation and deallocation of all dynamically allocated memory
- **Betty Coding Style**: Follows the Betty C coding standards for readability and consistency

## Architecture

```
┌─────────────────────────────────────────────────┐
│                    main()                        │
│  ┌──────────┐  ┌────────────┐  ┌──────────────┐ │
│  │Print     │→ │Parse Input │→ │Handle        │ │
│  │Prompt    │  │& Comments  │  │Multi-command │ │
│  └──────────┘  └────────────┘  │  Split       │ │
│                                └──────┬───────┘ │
│                                       │         │
│  ┌──────────────┐    ┌───────────────▼──────┐   │
│  │Builtin       │←── │Is Builtin?           │   │
│  │Commands      │    │(exit, env, cd, etc.) │   │
│  └──────────────┘    └───────────────┬──────┘   │
│                                      │          │
│  ┌──────────────┐    ┌───────────────▼──────┐   │
│  │execve()      │←── │PATH Lookup &         │   │
│  │(child proc)  │    │fork()                │   │
│  └──────────────┘    └──────────────────────┘   │
└─────────────────────────────────────────────────┘
```

## File Structure

| File | Description |
|------|-------------|
| `simple_shell.c` | Main entry point — reads input loop, forks, and waits for child processes |
| `print_prompt.c` | Displays the prompt and reads a line of input using `getline()` |
| `handle_comment.c` | Strips comments from input lines |
| `get_substrings.c` | Splits input into individual commands using `;` as delimiter |
| `get_command.c` | Parses a command line into the command name and argument array |
| `execute_command.c` | Calls `execve()` to execute the resolved command |
| `check_path.c` | Searches `PATH` directories for the executable |
| `handle_builtin.c` | Dispatches built-in command handlers |
| `is_builtin.c` | Checks if a command is a shell built-in |
| `cd.c` | Handles directory changes (HOME, OLDPWD, `-`, relative/absolute) |
| `print_env.c` | Prints all environment variables |
| `set_env.c` | Sets or updates an environment variable |
| `unset_env.c` | Removes an environment variable |
| `exit_shell.c` | Exits the shell with optional status code validation |
| `concatenate_env.c` | Builds `NAME=value` strings for the environment |
| `concatenate_path.c` | Builds full executable paths from directory + command |
| `_strlen.c` | Custom string length implementation |
| `_strcmp.c` | Custom string comparison implementation |
| `_strtok.c` | Custom string tokenizer |
| `_count_words.c` | Counts space-separated words in a string |
| `_is_number.c` | Validates whether a string is a valid integer |

## Requirements

- GCC compiler (`gcc`)
- Linux/Unix environment
- POSIX-compliant system headers

## Build

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Usage

### Interactive Mode

```bash
$ ./hsh
$ /bin/ls
$ echo "Hello, World!"
$ ls -la /tmp; echo done; env
```

### Non-Interactive Mode

```bash
$ echo "/bin/ls" | ./hsh
$ ./hsh < test_input.txt
```

### Built-in Commands

```bash
$ ./hsh
$ cd /tmp          # Change directory
$ cd -             # Go to previous directory
$ env              # Print environment
$ setenv MY_VAR hello   # Set environment variable
$ unsetenv MY_VAR       # Remove environment variable
$ exit             # Exit the shell
$ exit 42          # Exit with status code 42
```

## Tech Stack

- **Language**: C (C89/C90 standard)
- **System Calls**: `fork()`, `execve()`, `wait()`, `chdir()`, `getcwd()`, `stat()`, `access()`
- **I/O**: `getline()`, `write()`, `perror()`
- **Memory**: `malloc()`, `free()`, `strdup()`

## Coding Standard

This project follows the **Betty C coding style**, the standard used at ALX/Holberton:

- Functions are limited to a specific line count
- Variables are declared at the top of blocks
- Consistent brace placement and indentation
- Descriptive function and variable names
- Documentation comments for all functions

## Author

**Natnael Samson** — [Nattyy-1](https://github.com/Nattyy-1)
