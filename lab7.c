#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int execute(char **args);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s command [args...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *pipe_args[2][argc];
    int num_pipes = 0;
    int current_pipe = 0;
    pipe_args[0][0] = argv[1];

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "|") == 0) {
            if (current_pipe >= 1) {
                fprintf(stderr, "Error: only one pipe allowed\n");
                exit(EXIT_FAILURE);
            }
            pipe_args[current_pipe][i-1] = NULL;
            num_pipes++;
            current_pipe++;
            pipe_args[current_pipe][0] = argv[i+1];
            i++;
        } else {
            pipe_args[current_pipe][i] = argv[i];
        }
    }
    pipe_args[current_pipe+1][0] = NULL;


    int pipefd[2];
    int prev_pipe = 0;
    for (int i = 0; i <= num_pipes; i++) {
        if (pipe(pipefd) == -1) {
            perror("pipe error");
            exit(EXIT_FAILURE);
        }
        if (fork() == 0) {
            if (i != 0) {
                dup2(prev_pipe, STDIN_FILENO);
            }
            if (i != num_pipes) {
                dup2(pipefd[1], STDOUT_FILENO);
            }
            close(pipefd[0]);
            close(pipefd[1]);
            execute(pipe_args[i]);
            exit(EXIT_FAILURE);
        }
        if (prev_pipe != 0) {
            close(prev_pipe);
        }
        close(pipefd[1]);
        prev_pipe = pipefd[0];
    }
    for (int i = 0; i <= num_pipes; i++) {
        wait(NULL);
    }
    return 0;
}

int execute(char **args) {
    if (execvp(args[0], args) == -1) {
        perror("exec");
        exit(EXIT_FAILURE);
    }
    return 0;
}