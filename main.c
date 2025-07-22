#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "builtin_functions.h"

#define MAX_LINE 512
#define MAX_ARGS 100

int should_exit = 0;

void parse_command(char *line, char **args, int *argCounter) {
    *argCounter = 0;

    char *token = strtok(line, " \n");
    while (token != NULL && *argCounter < MAX_ARGS - 1) {
        args[(*argCounter)++] = token;
        token = strtok(NULL, " \n");
    }
    args[*argCounter] = NULL; // Null terminate the args array
}

void execute_command(char *cmd) {
    char *args[MAX_ARGS];
    int argCounter;
    parse_command(cmd, args, &argCounter);
    if (argCounter == 0) {
        return; // Skip empty commands
    }
    // Built in exit
    if (strcmp(args[0], "exit") == 0) {
        should_exit = 1;
        return;
    }
    // Built in cd
    if (strcmp(args[0], "cd") == 0) {
        builtin_functions_cd(args, argCounter);
        return;
    }
    // External command execution
    pid_t pid = fork();
    if (pid == 0) {
        execvp(args[0], args);
        perror("execvp failed");
        exit(1);
    } else if (pid > 0) {
        waitpid(pid, NULL, 0); // Parent waits
    } else {
        perror("fork failed");
    }
}

int main(int argc, char *argv[]) {
    FILE *input = stdin;
    // Handle batch mode
    if (argc == 2) {
        input = fopen(argv[1], "r");
        if (!input) {
            fprintf(stderr, "Error opening input file\n");
            exit(1);
        }
    } else if (argc > 2) {
        fprintf(stderr, "Too many arguments\n");
        exit(1);
    }
    char line[MAX_LINE];
    while (1) {
        if (input == stdin) {
            printf("prompt> "); // Prompt for interactive mode
        }

        if (!fgets(line, sizeof(line), input)) {
            break; // eof
        }

        // Split to handle multiple commands
        char *cmd = strtok(line, ";");
        while (cmd != NULL) {
            execute_command(cmd);
            cmd = strtok(NULL, ";");
        }

        if (should_exit) {
            break;
        }
    }

    if (input != stdin) {
        fclose(input);
    }
    return 0;
}
