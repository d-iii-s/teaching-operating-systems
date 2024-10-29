#include <stdlib.h>

#include "shared.h"

// Volatile used to avoid optimizing away allocations.
void * volatile p;

int main (void) {
    for (long i = 0 ; i < COUNT ; i++) {
        p = malloc (SIZE);
        free (p);
    }
    return (0);
}
