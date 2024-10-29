# Minishell

## Overview

Minishell is a project developed as part of the 42 school curriculum. The objective is to create a functional shell, similar to bash, implementing a subset of its features. This project provides experience in parsing, managing processes, handling signals, and memory management in C.

## Key Features

- **Command Parsing**: Interprets and executes user commands.
- **Built-in Functions**: Implements built-ins like `cd`, `echo`, `export`, `unset`, `exit`, etc.
- **Pipes and Redirections**: Handles pipes and I/O redirections.
- **Signal Handling**: Manages signals (e.g., `Ctrl+C`, `Ctrl+D`, and `Ctrl+\`) similar to bash.
  
## Getting Started

Clone the repository and compile the shell:

```bash
git clone https://github.com/n-andr/minishell.git
cd minishell
make

