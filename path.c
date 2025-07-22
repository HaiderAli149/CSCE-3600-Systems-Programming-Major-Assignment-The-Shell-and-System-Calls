```c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 1024
#define MAX_ARGS 64

// Global path variable
char *path[64];
int path_count = 0;

void init_path() {
    path[0] = strdup("/bin");
    path[1] = strdup("/usr/bin");
    path_count = 2;
}

void update_path(char *new_paths) {
    char *token = strtok(new_paths, ":");
    path_count = 0;
    while (token != NULL && path_count < 64) {
        path[path_count++] = strdup(token);
        token = strtok(NULL, ":");
    }
}

void print_path() {
    for (int i = 0; i < path_count; i++) {
        printf("%s
", path[i]);
    }
}

char *find_executable(char *command) {
    static char full_path[1024];
    for (int i = 0; i < path_count; i++) {
        snprintf(full_path, sizeof(full_path), "%s/%s", path[i], command);
        if (access(full_path, X_OK) == 0) {
            return full_path;
        }
    }
    return NULL;
}

void parse_input(char *line, char **args) {
    int i = 0;
    args[i] = strtok(line, " 	
");
    while (args[i] != NULL && i < MAX_ARGS - 1) {
        args[++i] = strtok(NULL, " 	
");
    }
    args[i] = NULL;
}

void execute_command(char **args) {
    if (args[0] == NULL) return;

    // Built-in: exit
    if (strcmp(args[0], "exit") == 0) {
        exit(0);
    }
    // Built-in: cd
    else if (strcmp(args[0], "cd") == 0) {
        if (args[1]) chdir(args[1]);
        else fprintf(stderr, "cd: missing argument\n");
    }
    // Built-in: path
    else if (strcmp(args[0], "path") == 0) {
        if (args[1] == NULL) print_path();
        else {
            for (int i = 1; args[i] != NULL; i++) {
                path[i-1] = strdup(args[i]);
            }
            path_count = 0;
            while (args[path_count+1] != NULL) path_count++;
        }
    }
    // External commands
    else {
        char *exec_path = find_executable(args[0]);
        if (exec_path == NULL) {
            fprintf(stderr, "Command not found: %s\n", args[0]);
            return;
        }
        pid_t pid = fork();
        if (pid == 0) {
            execv(exec_path, args);
            perror("execv failed");
            exit(1);
        } else {
            wait(NULL);
        }
    }
}

int main() {
    char line[MAX_LINE];
    char *args[MAX_ARGS];

    init_path();

    while (1) {
        printf("myshell> ");
        if (!fgets(line, MAX_LINE, stdin)) break;
        parse_input(line, args);
        execute_command(args);
    }

    return 0;
}

```
