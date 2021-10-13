#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <mimalloc.h>

int main (void) {
    for (int i = 0 ; i < 256 ; i++) {
        void *p = mi_malloc (i);
        void *q = mi_malloc (i);
        int delta = (uintptr_t) q - (uintptr_t) p;
        printf ("allocating %i bytes consumes %i bytes\n", i, delta);
    }
    return (0);
}
