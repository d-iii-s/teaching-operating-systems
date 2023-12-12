#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>


#define CYCLES 10000000


int main (void) {
    struct timespec time_before, time_after;

    clock_gettime (CLOCK_MONOTONIC_RAW, &time_before);
    for (int i = 0 ; i < CYCLES ; i ++) {
        getpid ();
    }
    clock_gettime (CLOCK_MONOTONIC_RAW, &time_after);

    uint64_t time = ((time_after.tv_sec * 1000000000ull + time_after.tv_nsec) - (time_before.tv_sec * 1000000000ull + time_before.tv_nsec)) / CYCLES;
    printf ("Average syscall time %d ns\n", time);

    return (0);
}
