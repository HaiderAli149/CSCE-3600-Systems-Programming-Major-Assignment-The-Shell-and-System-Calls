# Compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Target executable
TARGET = newshell

# Source and object files
SRC = main.c builtin_functions.c
OBJ = $(SRC:.c=.o)

# Default rule
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Compile .c files into .o files
%.o: %.c builtin_functions.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up compiled files
clean:
	rm -f $(OBJ) $(TARGET)
