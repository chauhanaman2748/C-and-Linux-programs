#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>

#define ARR_SIZE 100
#define MIN_VAL 10
#define MAX_VAL 20

int ia1[ARR_SIZE], ia2[ARR_SIZE], ia3[ARR_SIZE];

void *sum_1(void *arg)
{
    int *arr = (int *)arg;
    int sum = 0;
    for (int i = 0; i < ARR_SIZE; i++)
    {
        sum += arr[i];
    }
    pthread_exit((void *)(intptr_t)sum);
}

void *sum_2(void *arg)
{
    int *arr = (int *)arg;
    int sum = 0;
    for (int i = 0; i < ARR_SIZE; i++)
    {
        sum += arr[i];
    }
    pthread_exit((void *)(intptr_t)sum);
}

void *sum_3(void *arg)
{
    int *arr = (int *)arg;
    int sum = 0;
    for (int i = 0; i < ARR_SIZE; i++)
    {
        sum += arr[i];
    }
    pthread_exit((void *)(intptr_t)sum);
}

int main()
{
    for (int i = 0; i < ARR_SIZE; i++)
    {
        ia1[i] = rand() % (MAX_VAL - MIN_VAL + 1) + MIN_VAL;
        ia2[i] = rand() % (MAX_VAL - MIN_VAL + 1) + MIN_VAL;
        ia3[i] = rand() % (MAX_VAL - MIN_VAL + 1) + MIN_VAL;
    }

    pthread_t thread1, thread2, thread3;
    pthread_create(&thread1, NULL, sum_1, (void *)ia1);
    pthread_create(&thread2, NULL, sum_2, (void *)ia2);
    pthread_create(&thread3, NULL, sum_3, (void *)ia3);

    intptr_t sum1, sum2, sum3;

    pthread_join(thread1, (void **)&sum1);
    pthread_join(thread2, (void **)&sum2);
    pthread_join(thread3, (void **)&sum3);

    printf("Sum of all the elements: %ld\n", sum1 + sum2 + sum3);

    return 0;
}
