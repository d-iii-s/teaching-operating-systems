#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>

#define COUNTERS 256
#define LOOPS 1000000000

int counters [COUNTERS];

void *counter_thread_body (void *arguments) {
    volatile int *counter = (volatile int *) arguments;
    for (int i = 0 ; i < LOOPS ; i ++) {
        (*counter) ++;
    }
    return (NULL);
}

int main (int argc, char *argv []) {

    // One counter index comes from command line.
    assert (argc == 2);
    int index = atoi (argv [1]);
    assert ((index >= 0) && (index < COUNTERS));

    pthread_t thread_one, thread_two;

    // Launch two threads that both execute the same body.
    // Each thread will increment a different counter.
    pthread_create (&thread_one, NULL, counter_thread_body, &counters [0]);
    pthread_create (&thread_two, NULL, counter_thread_body, &counters [index]);
    // Wait for the two threads to finish.
    pthread_join (thread_one, NULL);
    pthread_join (thread_two, NULL);

    return (0);
}
