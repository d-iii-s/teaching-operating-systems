#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_body (void *arguments) {
    return (NULL);
}

int main (int argc, char *argv []) {
    int loops = 1000;
    if (argc == 2) {
        loops = atoi (argv [1]);
    }

    // Did we say large arrays on stack are not good ?
    pthread_t threads [loops];

    // First create and then join all threads.
    struct timespec time_before;
    clock_gettime (CLOCK_MONOTONIC_RAW, &time_before);
    for (int i = 0 ; i < loops ; i ++) {
        pthread_create (&threads [i], NULL, thread_body, NULL);
    }
    for (int i = 0 ; i < loops ; i ++) {
        pthread_join (threads [i], NULL);
    }
    struct timespec time_after;
    clock_gettime (CLOCK_MONOTONIC_RAW, &time_after);

    double time = time_after.tv_sec * 1e9 + time_after.tv_nsec - time_before.tv_sec * 1e9 - time_before.tv_nsec;

    printf ("Loop count is %i.\n", loops);
    printf ("Time per single iteration is %f ns.\n", time / loops);

    return (0);
}
