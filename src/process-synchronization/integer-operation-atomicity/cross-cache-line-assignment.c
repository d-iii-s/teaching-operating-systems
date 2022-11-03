#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <inttypes.h>

#define CACHE_LINE_SIZE 64

// A buffer that spans two cache lines.
volatile int8_t shared [CACHE_LINE_SIZE * 2] __attribute__ ((aligned (CACHE_LINE_SIZE)));
volatile int64_t *value;

void *writer_thread_body (void *arguments) {
    while (true) {
        *value = 0;
        *value = -1;
    }
}

int main (int argc, char *argv []) {

    pthread_t thread;

    // Compute variable address residing across cache line boundary.
    value = (int64_t *) (shared + CACHE_LINE_SIZE - sizeof (int64_t)/2);
    printf ("Address is %p.\n", value);
    *value = 0;

    // Launch the updater thread.
    pthread_create (&thread, NULL, writer_thread_body, NULL);

    // Keep watching for unusual values.
    while (true) {
        volatile int64_t snapshot = *value;
        if ((snapshot != 0) && (snapshot != -1)) {
            printf ("Observed %" PRId64 ".\n", snapshot);
        }
    }
}
