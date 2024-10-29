#include <alloca.h>

#include "shared.h"

void allocate_and_free (void) {
    void *p = alloca (SIZE);
}

int main (void) {
    for (long i = 0 ; i < COUNT ; i++) {
        allocate_and_free ();
    }
    return (0);
}
