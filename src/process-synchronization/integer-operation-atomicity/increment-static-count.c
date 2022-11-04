#include <stdio.h>
#include <pthread.h>

volatile int counter = 0;

#define LOOPS 1000000000

void *counter_thread_body (void *arguments) {
    for (int i = 0 ; i < LOOPS ; i ++) {
        counter ++;
    }
    return (NULL);
}

int main (void) {
    pthread_t thread_one, thread_two;

    // Launch two threads that both execute the same body.
    pthread_create (&thread_one, NULL, counter_thread_body, NULL);
    pthread_create (&thread_two, NULL, counter_thread_body, NULL);
    // Wait for the two threads to finish.
    pthread_join (thread_one, NULL);
    pthread_join (thread_two, NULL);

    printf ("Loop count is %i.\n", LOOPS);
    printf ("Counter value is %i.\n", counter);

    return (0);
}
