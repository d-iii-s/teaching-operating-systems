#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

volatile int loops = 1000000;

sem_t ping_semaphore, pong_semaphore;

void *ping_thread_body (void *arguments) {
    for (int i = 0 ; i < loops ; i ++) {
        sem_post (&ping_semaphore);
        sem_wait (&pong_semaphore);
    }
    return (NULL);
}

void *pong_thread_body (void *arguments) {
    for (int i = 0 ; i < loops ; i ++) {
        sem_wait (&ping_semaphore);
        sem_post (&pong_semaphore);
    }
    return (NULL);
}

int main (int argc, char *argv []) {
    if (argc == 2) {
        loops = atoi (argv [1]);
    }

    pthread_t ping_thread, pong_thread;

    // Initialize the semaphores.
    sem_init (&ping_semaphore, 0, 0);
    sem_init (&pong_semaphore, 0, 0);

    // Launch two threads that ping pong.
    struct timespec time_before;
    clock_gettime (CLOCK_MONOTONIC_RAW, &time_before);
    pthread_create (&ping_thread, NULL, ping_thread_body, NULL);
    pthread_create (&pong_thread, NULL, pong_thread_body, NULL);
    // Wait for the two threads to finish.
    pthread_join (ping_thread, NULL);
    pthread_join (pong_thread, NULL);
    struct timespec time_after;
    clock_gettime (CLOCK_MONOTONIC_RAW, &time_after);

    double time = time_after.tv_sec * 1e9 + time_after.tv_nsec - time_before.tv_sec * 1e9 - time_before.tv_nsec;

    printf ("Loop count is %i.\n", loops);
    printf ("Time per ping pong is %f ns.\n", time / loops);

    return (0);
}
