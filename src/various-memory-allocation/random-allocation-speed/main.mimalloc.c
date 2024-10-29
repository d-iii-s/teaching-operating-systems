#include <stdlib.h>
#include <mimalloc.h>

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
        if (blocks [block]) mi_free (blocks [block]);
        blocks [block] = mi_malloc (random () % SIZE);
    }
    for (long i = 0 ; i < LIVE ; i ++) {
        mi_free (blocks [i]);
    }
    return (0);
}
