#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

volatile int counter = 0;
volatile int loops = 100000000;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *counter_thread_body (void *arguments) {
    for (int i = 0 ; i < loops ; i ++) {
        pthread_mutex_lock (&mutex);
        counter ++;
        pthread_mutex_unlock (&mutex);
    }
    return (NULL);
}

int main (int argc, char *argv []) {
    if (argc == 2) {
        loops = atoi (argv [1]);
    }

    pthread_t thread_one, thread_two;

    // Launch two threads that both execute the same body.
    pthread_create (&thread_one, NULL, counter_thread_body, NULL);
    pthread_create (&thread_two, NULL, counter_thread_body, NULL);
    // Wait for the two threads to finish.
    pthread_join (thread_one, NULL);
    pthread_join (thread_two, NULL);

    printf ("Loop count is %i.\n", loops);
    printf ("Counter value is %i.\n", counter);

    return (0);
}
