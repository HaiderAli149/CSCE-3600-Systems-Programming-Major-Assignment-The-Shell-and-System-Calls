/*
 * myhistory.c
 * This file is for the myhistory command in our shell project.
 * It saves the last 20 commands and lets you view, clear, or re-run them.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HISTORY_SIZE 20

char *history[HISTORY_SIZE];
int history_count = 0;

// This adds a command to history
void add_to_history(const char *cmd) {
    if (history_count < HISTORY_SIZE) {
        history[history_count++] = strdup(cmd);
    } else {
        free(history[0]); // remove the oldest one
        for (int i = 1; i < HISTORY_SIZE; i++) {
            history[i - 1] = history[i];
        }
        history[HISTORY_SIZE - 1] = strdup(cmd);
    }
}

// This prints the list of saved commands
void print_history() {
    for (int i = 0; i < history_count; i++) {
        printf("%d: %s", i + 1, history[i]);
    }
}

// This clears the whole history
void clear_history() {
    for (int i = 0; i < history_count; i++) {
        free(history[i]);
    }
    history_count = 0;
}

// This runs a previous command using its number
void execute_history(int index) {
    if (index < 1 || index > history_count) {
        fprintf(stderr, "Invalid command number\n");
        return;
    }

    printf("Running: %s", history[index - 1]);
    system(history[index - 1]); // just runs it with system()
}

// This frees the memory when done
void free_history() {
    for (int i = 0; i < history_count; i++) {
        free(history[i]);
    }
}
