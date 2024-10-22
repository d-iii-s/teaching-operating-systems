#include <stdlib.h>

#include "shared.h"

int main (void) {
    for (long i = 0 ; i < COUNT ; i++) {
        void *p = malloc (SIZE);
        free (p);
    }
    return (0);
}
