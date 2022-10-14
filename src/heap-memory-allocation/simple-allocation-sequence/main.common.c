#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main (void) {
    int size;
    int step;
    while (true) {
        scanf ("%i %i", &size, &step);
        void *last = NULL;
        for (int i = 0 ; i < 64 ; i++) {
            void *this = malloc (size);
            printf ("size %i: address %x difference %i\n", size, this, this - last);
            size += step;
            last = this;
        }
    }
}
