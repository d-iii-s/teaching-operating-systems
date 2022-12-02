#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/stat.h>

#include "common.h"

int data [PAGE_SIZE / sizeof (int)];

int main (int argc, char *argv []) {

    memset (data, 0, sizeof (data));

    int file = open (FILE_NAME, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

    while (true) {
        data [0] ++;
        lseek (file, 0, SEEK_SET);
        write (file, data, sizeof (data));
        printf ("Normal write with value %i.\n", data [0]);
        sleep (WRITER_DELAY);
    }

    close (file);

    return (0);
}
