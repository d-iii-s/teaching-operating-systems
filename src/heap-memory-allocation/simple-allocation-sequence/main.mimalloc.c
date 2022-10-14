#include <stdio.h>
#include <stdbool.h>
#include <mimalloc.h>

int main (void) {
    int size;
    int step;
    while (true) {
        scanf ("%i %i", &size, &step);
        void *last = NULL;
        for (int i = 0 ; i < 64 ; i++) {
            void *this = mi_malloc (size);
            printf ("size %i: address %x difference %i\n", size, this, this - last);
            size += step;
            last = this;
        }
    }
}
