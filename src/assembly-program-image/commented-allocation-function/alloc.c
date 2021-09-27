#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

void *safe_malloc (size_t size) {
    void *result = malloc (size);
    if (result == NULL) {
        printf ("Failed to allocate %zi bytes.\n", size);
        exit (ENOMEM);
    }
    return (result);
}
