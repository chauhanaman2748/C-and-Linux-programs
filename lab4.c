#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
   pid_t pid_c1, pid_c2;

   pid_c1 = fork();
   pid_c2 = fork();

   if(pid_c1 == 0) {

      if(pid_c2 == 0) {
         printf("GC: Grandchild process started\n");

         if(chdir("/home/chauhanaman2748/lab4") == -1) {
            perror("GC: Error changing directory");
            exit(1);
         }

         // Creating file with 0777
         int fd = open("sample.txt", O_CREAT | O_WRONLY, 0777);
         if(fd == -1) {
            perror("GC: Error creating file");
            exit(1);
         }
         close(fd);

         printf("GC: File created\n");
         exit(0);
      } else if(pid_c2 == -1) {
         perror("C1: Error forking grandchild");
         exit(1);
      }
      else{
        printf("C1: Child process started\n");
        int status;
         waitpid(pid_c2, &status, 0);
         if(WIFEXITED(status)) {
            printf("C1: Grandchild exited normally\n");

            char *args[] = {"ls", "-1", "/home/chauhanaman2748/lab4", NULL};
            execv("/bin/ls", args);

            // If execv() fails
            perror("C1: Error executing ls");
            exit(1);
         }
      }

   } else if(pid_c1 == -1) {
      perror("Main: Error forking first child");
      exit(1);
   }

   if(pid_c1 != 0 && pid_c2 == 0) {
      printf("C2: Child process started\n");

      execl("/bin/ls", "ls", "-1", "/home/chauhanaman2748", NULL);

      perror("C2: Error executing ls");
      exit(1);
   } else if(pid_c2 == -1) {
      perror("Main: Error forking second child");
      exit(1);
   }

   int status;
   waitpid(pid_c1, &status, 0);
   waitpid(pid_c2, &status, 0);

   printf("Main: All child processes completed\n");
   return 0;
}
