#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>

pthread_mutex_t mutex_one = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_two = PTHREAD_MUTEX_INITIALIZER;

void *thread_one_body (void *arguments) {
    int i = 0;
    while (true) {
        pthread_mutex_lock (&mutex_one);
        pthread_mutex_lock (&mutex_two);
        printf ("Thread one %d\n", i);
        pthread_mutex_unlock (&mutex_two);
        pthread_mutex_unlock (&mutex_one);
        i ++;
        sleep (1);
    }
}

void *thread_two_body (void *arguments) {
    int i = 0;
    while (true) {
        pthread_mutex_lock (&mutex_two);
        pthread_mutex_lock (&mutex_one);
        printf ("Thread two %d\n", i);
        pthread_mutex_unlock (&mutex_one);
        pthread_mutex_unlock (&mutex_two);
        i ++;
        sleep (1);
    }
}

int main (int argc, char *argv []) {

    pthread_t thread_one, thread_two;

    pthread_create (&thread_one, NULL, thread_one_body, NULL);
    pthread_create (&thread_two, NULL, thread_two_body, NULL);
    pthread_join (thread_one, NULL);
    pthread_join (thread_two, NULL);

    return (0);
}
