#include <mimalloc.h>

#include "shared.h"

// Volatile used to avoid optimizing away allocations.
void * volatile p;

int main (void) {
    for (int i = 0 ; i < COUNT ; i++) {
        p = mi_malloc (SIZE);
        mi_free (p);
    }
    return (0);
}
