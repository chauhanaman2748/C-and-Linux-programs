#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

volatile int count = 0;
volatile long last_signal_time = 0;

void signal_handler(int sig) {
    long current_time = (long) time(NULL);
    printf("\ntime: %ld\n",current_time);
    if (sig == SIGINT) {
        if (current_time - last_signal_time <= 5) {
            count++;
        } else {
            count = 1;
        }
        last_signal_time = current_time;
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
