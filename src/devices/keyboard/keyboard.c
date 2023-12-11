#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include <sys/io.h>

#define KEYBOARD 0x60

int main (int argc, char *argv []) {

    ioperm (KEYBOARD, KEYBOARD, true);

    uint8_t last = 0;
    while (true) {
        uint8_t this;
        do {
            // This displays scan code whenever it changes.
            // Autorepeat is therefore not visible. Real
            // driver would read on interrupt instead.
            this = inb (KEYBOARD);
        } while (this == last);
        printf ("%hhx\n", this);
        last = this;
    }
}
