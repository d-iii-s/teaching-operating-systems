#include <stdlib.h>

#include "shared.h"

// Volatile used to avoid optimizing away allocations.
void * volatile blocks [LIVE];

int main (void) {
    for (long i = 0 ; i < LIVE ; i ++) {
        blocks [i] = NULL;
    }
    srandom (0);
    for (long i = 0 ; i < COUNT ; i++) {
        long block = random () % LIVE;
        if (blocks [block]) free (blocks [block]);
        blocks [block] = malloc (random () % SIZE);
    }
    for (long i = 0 ; i < LIVE ; i ++) {
        free (blocks [i]);
    }
    return (0);
}
