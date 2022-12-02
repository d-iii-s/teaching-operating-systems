#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#include "common.h"

int data [PAGE_SIZE / sizeof (int)];

int main (int argc, char *argv []) {

    int file = open (FILE_NAME, O_CREAT | O_RDWR);

    while (true) {
        lseek (file, 0, SEEK_SET);
        read (file, data, sizeof (data));
        printf ("Normal read with value %i.\n", data [0]);
        sleep (READER_DELAY);
    }

    close (file);

    return (0);
}
