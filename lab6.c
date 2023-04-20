#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>


int flag=0;
pid_t a[4];

void handle_sigint(int sig) {
    printf("PID=%d PPID=%d terminated\n", getpid(), getppid());
    exit(0);
}


int main() {
    pid_t pid1, pid2, pid3;

    pid1 = fork();
    pid2 = fork();
    pid3 = fork();

//////////////////////////////////////////////////

    if (pid1 == 0 && pid3 != 0 && pid2 != 0) {
        printf("Child 1 (PID=%d) created\n", getpid());
        a[1]=getpid();
        signal(SIGINT, SIG_IGN);
        while(1) {
            if(flag==1){
                printf("This statement is from C1 process %d\n",getpid());
                sleep(2);
                kill(a[2], SIGCONT);
                kill(a[1], SIGSTOP);
                kill(a[1], SIGSTOP);
            }
            else{
                printf("This statement is from C1 process %d\n",getpid());
                sleep(2);
                int status;
                if(waitpid(0, &status, 0)){
                    waitpid(0, &status, 0);
                    flag=1;
                    //kill(a[1], SIGSTOP);
                }
            }            
        }
    }

/////////////////////////////////////////
    if (pid1 == 0 && pid2 == 0 && pid3 != 0) {
        printf("Grandchild 1 (PID=%d) created\n", getpid());
        signal(SIGINT, handle_sigint);
        while(1) {
            printf("This statement is from GC1 process %d\n",getpid());
            sleep(2);
        }
    }
    else if(pid1 > 0 && pid2 == 0 && pid3 != 0){
        printf("Child 2 (PID=%d) created\n", getpid());
        a[2]=getpid();
        signal(SIGINT, SIG_IGN);
        while(1) {
            if(flag==1){
                kill(a[2], SIGSTOP);
                printf("This statement is from C2 process %d\n",getpid());
                sleep(2);
                kill(a[3], SIGCONT);
                kill(a[2], SIGSTOP);
            }            
            else {
                printf("This statement is from C2 process %d\n",getpid());
                sleep(2);
                int status;
                if(waitpid(0, &status, 0)){
                    flag=1;
                    //kill(a[2], SIGSTOP);
                }
            } 
        }
    }

/////////////////////////////////////////
    
    if(pid1 > 0 && pid2 != 0 && pid3 == 0){
        printf("Child 3 (PID=%d) created\n", getpid());
        a[3]=getpid();
        signal(SIGINT, SIG_IGN);
        while(1) {
            if(flag==1){
                kill(a[3], SIGSTOP);
                kill(a[3], SIGSTOP);
                printf("This statement is from C3 process %d\n",getpid());
                sleep(2);
                kill(a[1], SIGCONT);
                //kill(a[3], SIGSTOP);
            }
            else {
                printf("This statement is from C3 process %d\n",getpid());
                sleep(2);
                int status;
                if(waitpid(0, &status, 0)){
                    flag=1;
                    //kill(a[3], SIGSTOP);
                }
            } 
        }
    }
    else if(pid1 == 0 && pid2 != 0 && pid3 == 0){
        printf("Grandchild 2 (PID=%d) created\n", getpid());
        signal(SIGINT, handle_sigint);
        while(1) {
            printf("This statement is from GC2 process %d\n",getpid());
            sleep(2);
        }
    }
    else if(pid1 > 0 && pid2 == 0 && pid3 == 0){
        printf("Grandchild 3 (PID=%d) created\n", getpid());
        signal(SIGINT, handle_sigint);
        while(1) {
            printf("This statement is from GC3 process %d\n",getpid());
            sleep(2);
        }
    }
    else if(pid1 == 0 && pid2 == 0 && pid3 == 0){
        printf("Child of grandchild (PID=%d) created\n", getpid());
        signal(SIGINT, handle_sigint);
        while(1) {
            printf("This statement is from GCC process %d\n",getpid());
            sleep(2);
        }
    }

////////////////////////////////////////////
    if (pid1 != 0 && pid2 != 0 && pid3 != 0) {
        printf("Parent (PID=%d) created children: %d %d %d\n", getpid(), pid1, pid2, pid3);
        setpgid(0, pid1); 
        a[0]=getpid();
        signal(SIGINT, SIG_IGN);
        int status;
        waitpid(0, &status, 0);
    }

    return 0;
}