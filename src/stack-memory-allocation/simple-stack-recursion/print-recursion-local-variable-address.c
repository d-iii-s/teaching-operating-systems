#include <stdio.h>

int test (int depth) {
    int i = 1234;
    printf ("%p\n", &i);
    if (depth > 0) test (depth - 1);
}

int main (void) {
    test (10);
    printf ("main: %p\n", main);
}
