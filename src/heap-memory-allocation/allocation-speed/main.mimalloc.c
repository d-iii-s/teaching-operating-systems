#include <mimalloc.h>

#include "shared.h"

int main (void) {
    for (int i = 0 ; i < COUNT ; i++) {
        void *p = mi_malloc (SIZE);
        mi_free (p);
    }
    return (0);
}
