# CSCE 3600 – Systems Programming  
## Major Assignment 2: The Shell and System Calls

### Group Members
- **Haider Beg**
- **Jake Moseley**
- **Oyindamola Bade-Ojo**
- **Hasan Walid**

---

### Project Organization

Each member was responsible for one of the built in functions. The project is broken into the following components:

- **`builtin_functions.c` – cd command**  
  *Implemented by: Haider Beg*  
  Implements a function that counts the number of leading zero bits in a 32-bit unsigned integer using only bitwise operations.

- **`builtin_functions.c` – exit command**  
  *Implemented by: Jake Moseley*  
  Exits the shell after completing all commands on the current line. Uses a global flag to ensure proper termination.

- **`builtin_functions.c` – myhistory command**  
  *Implemented by: Oyindamola Bade-Ojo*  
  - 

- **`builtin_functions.c` – path command**  
  *Implemented by: Hasan Walid*  
  - 

- **`main.c` – Main Shell Engine**  
  *Implemented by: Haider Beg & Jake Moseley*  
  Handles interactive and batch modes, parses commands, supports multiple commands per line (;), forks child processes, and manages execution.

- **`builtin_functions.c` – Header File**  
  *Implemented by: Haider Beg & Jake Moseley*  
  Declares all built-in command functions and shared variables.

- **`README.md`**  
  *Written by: Jake Moseley*  
  Contains project description, member responsibilities, and build/run instructions.

---

### Known Bugs or Issues

- There are currently **no known bugs**.  
  All functions have been tested and verified to work correctly with a variety of inputs.

---
