#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 1024
#define MAX_ARGS 64
#define DELIM " \t\r\n\a"

int main() {
    char line[MAX_LINE];
    char *args[MAX_ARGS];
    pid_t pid;
    int status;

    while (1) {
        printf("my_shell> ");
        
        if (!fgets(line, MAX_LINE, stdin)) break;

        int i = 0;
        args[i] = strtok(line, DELIM);
        while (args[i] != NULL) {
            i++;
            args[i] = strtok(NULL, DELIM);
        }

        if (args[0] == NULL) continue;
        if (strcmp(args[0], "exit") == 0) break;

        pid = fork();
        if (pid == 0) {
            if (execvp(args[0], args) == -1) {
                perror("shell_error");
            }
            exit(EXIT_FAILURE);
        } else if (pid < 0) {
            perror("fork_error");
        } else {
            do {
                waitpid(pid, &status, WUNTRACED);
            } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        }
    }

    return 0;
}