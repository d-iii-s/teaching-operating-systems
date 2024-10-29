#include <alloca.h>

#include "shared.h"

// Volatile used to avoid optimizing away allocations.
void * volatile p;

void allocate_and_free (void) {
    p = alloca (SIZE);
}

int main (void) {
    for (long i = 0 ; i < COUNT ; i++) {
        allocate_and_free ();
    }
    return (0);
}
