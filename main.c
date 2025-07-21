#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "builtin_functions.h"

#define MAX_LINE 512
#define MAX_ARGS 100

void parse_command(char *line, char **args, int *argCounter) {
    *argCounter = 0;

    char *token = strtok(line, " \n");
    while (token != NULL && *argCounter < MAX_ARGS - 1) {
        args[(*argCounter)++] = token;
        token = strtok(NULL, " \n");
    }
    args[*argCounter] = NULL; // Null-terminate the args array
}

int main()
{
    char line[MAX_LINE];
    char *args[MAX_ARGS];
    int argCounter;

    while(1) 
    {
        printf("prompt> ");
        if (fgets(line, sizeof(line), stdin) == NULL) 
        {
            printf("\n");
            break; // Exit on EOF
        }

        parse_command(line, args, &argCounter);

        if(argCounter == 0) 
        {
            continue; // Skip empty lines
        }

        if(strcmp(args[0], "exit") == 0)
        {
            exit(0);
        }

        if(strcmp(args[0], "cd") == 0)
        {
            builtin_functions_cd(args, argCounter);
            continue; // Skip to the next iteration after handling cd
        }

        pid_t pid = fork();
        if(pid == 0)
        {
            execvp(args[0], args);
            perror("execvp failed");
            exit(1);
        }
        else if(pid < 0)
        {
            waitpid(pid, NULL, 0);
        }
        else
        {
            perror("fork failed");
        }
    }

    return 0; 
}