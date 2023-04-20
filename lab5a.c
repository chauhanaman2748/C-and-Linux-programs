#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

volatile int count = 0;
time_t last_signal_time = 0;

void signal_handler(int sig) {
    time_t current_time = time(NULL);
    if (sig == SIGINT) {
        if (current_time - last_signal_time <= 5) {
            last_signal_time = current_time;
            count++;
        } else {
            last_signal_time = current_time;
            count = 1;
        }
        
        if (count == 2) {
            printf("\nExited with 2 ctrl c within 5 sec.\n");
            exit(0);
        }
    }
}

int main() {
    signal(SIGINT, signal_handler);

    while (1) {
        printf("\nWelcome to Lab5 -Signals\n");
        sleep(1);
    }
    return 0;
}
