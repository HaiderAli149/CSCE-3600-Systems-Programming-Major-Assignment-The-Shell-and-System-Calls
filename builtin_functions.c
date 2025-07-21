#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "builtin_functions.h"

// Function to change the current directory
// Handles "cd" command with no arguments, one argument, or too many arguments
void builtin_functions_cd(char **args, int argCounter) 
{
    if (argCounter == 1) 
    {
        char *home = getenv("HOME");
        if (home == NULL) 
        {
            fprintf(stderr, "cd: HOME not set\n");
        } 
        else 
        {
            if (chdir(home) != 0) 
            {
                perror("cd");
            }
        }
    } 
    else if (argCounter == 2) 
    {
        if (chdir(args[1]) != 0) 
        {
            perror("cd");
        }
    } 
    else 
    {
        fprintf(stderr, "cd: too many arguments\n");
    }
}
