#include <time.h>
#include <fcntl.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>


#define CYCLES 100000
#define BLOCK 1048576


int main (void) {
    struct timespec time_before, time_after;
    uint64_t time_delta;

    int file_zero = open ("/dev/zero", O_RDONLY);
    assert (file_zero >= 0);

    char buffer [BLOCK];
    char target [BLOCK];
    ssize_t read_status;

    // Warm up call to page in buffer.
    read_status = read (file_zero, buffer, BLOCK);
    assert (read_status == BLOCK);

    clock_gettime (CLOCK_MONOTONIC_RAW, &time_before);
    for (int i = 0 ; i < CYCLES ; i ++) {
        read_status = read (file_zero, buffer, BLOCK);
        assert (read_status == BLOCK);
    }
    clock_gettime (CLOCK_MONOTONIC_RAW, &time_after);

    close (file_zero);

    time_delta = ((time_after.tv_sec * 1000000000ull + time_after.tv_nsec) - (time_before.tv_sec * 1000000000ull + time_before.tv_nsec)) / CYCLES;
    printf ("Average syscall time %d ns\n", time_delta);

    // Warm up call to page in target.
    memcpy (target, buffer, BLOCK);

    clock_gettime (CLOCK_MONOTONIC_RAW, &time_before);
    for (int i = 0 ; i < CYCLES ; i ++) {
        // Compile without optimization because compiler understands memcpy.
        memcpy (target, buffer, BLOCK);
    }
    clock_gettime (CLOCK_MONOTONIC_RAW, &time_after);

    time_delta = ((time_after.tv_sec * 1000000000ull + time_after.tv_nsec) - (time_before.tv_sec * 1000000000ull + time_before.tv_nsec)) / CYCLES;
    printf ("Average copy time %d ns\n", time_delta);

    return (0);
}
