#include <stdio.h>

int *test (void) {
    int i = 1234;
    return (&i);
}

int main (void) {
    int *addr = test ();
    printf ("%p\n", addr);
}
