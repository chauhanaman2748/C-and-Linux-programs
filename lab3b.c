#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t child_pid, grandchild_pid, grandchild2_pid;
    
    child_pid = fork();
    grandchild_pid = fork();
    grandchild2_pid = fork();
    
    if (child_pid == 0)
    {        
        if (grandchild_pid == 0)
        {
            printf("Printing from grand child: Welcome to COMP 8567\n");
            printf("Grandchild process (PID: %d) (PPID: %d)\n", getpid(), getppid());
            if (grandchild2_pid == 0)
            {
                printf("Printing from grand child's child: Welcome to COMP 8567\n");
                printf("Grandchild's child process (PID: %d) (PPID: %d)\n", getpid(), getppid());
            }
            else if (child_pid<0)    printf("ERROR\n");
            else
            {
                printf("(PID: %d) (PPID: %d)\n", getpid(), getppid());
                wait(NULL);
            }
        }
        else if (child_pid<0)    printf("ERROR\n");
        else
        {
            printf("(PID: %d) (PPID: %d)\n", getpid(), getppid());
            wait(NULL);
        }
    }
    else if (child_pid<0)    printf("ERROR\n");
    else
    {
        printf("(PID: %d) (PPID: %d)\n", getpid(), getppid());
        wait(NULL);
    }   
    return 0;
}