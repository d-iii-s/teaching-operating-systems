#include <fcntl.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/mman.h>

#include "common.h"

int main (int argc, char *argv []) {

    int file = open (FILE_NAME, O_RDWR);
    int *data = (int *) mmap (NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, file, 0);

    assert (data != MAP_FAILED);

    while (true) {
        data [0] ++;
        printf ("Mapped write with value %i.\n", data [0]);
        sleep (WRITER_DELAY);
    }

    munmap (data, PAGE_SIZE);
    close (file);

    return (0);
}
