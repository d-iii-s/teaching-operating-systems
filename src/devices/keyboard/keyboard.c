#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include <sys/io.h>

#define DURATION 60

#define KEYBOARD 0x60

int main (int argc, char *argv []) {

    ioperm (KEYBOARD, KEYBOARD, true);

    struct timespec start;
    clock_getres (CLOCK_REALTIME, &start);

    uint8_t last = 0;
    while (true) {
        uint8_t this;
        do {
            // Terminate after preset duration
            // because breaking from keyboard
            // may not work.
            struct timespec now;
            clock_getres (CLOCK_REALTIME, &now);
            if (now.tv_sec + now.tv_nsec / 1e9 - start.tv_sec - start.tv_nsec / 1e9 > DURATION) {
                exit (0);
            }

            // This displays scan code whenever it changes.
            // Autorepeat is therefore not visible. Real
            // driver would read on interrupt instead.
            this = inb (KEYBOARD);
        } while (this == last);
        printf ("%hhx\n", this);
        last = this;
    }
}
