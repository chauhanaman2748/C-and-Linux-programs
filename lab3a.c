#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>

int main() {
    pid_t child_pid = fork();
    int status;

    if (child_pid == 0) {
        // child process
        for (int i = 0; i < 30; i++) {
            printf("Child process ID: %d, Parent process ID: %d\n", getpid(), getppid());
            sleep(1);
        }
        exit(0);
    } 
    else if (child_pid<0)    printf("ERROR\n");
    else {
        // parent process
        wait(&status);
        if (WIFEXITED(status)) {
            printf("Child terminated normally with exit status %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child terminated due to signal %d\n", WTERMSIG(status));
        }
    }

    return 0;
}