#include <stdio.h>
#include <stdbool.h>

int offset;

void function (int a, int b, int c) {
    int i = 1;
    int j = 2;
    int k = 3;

    *(((char *) &k) + offset) = 0xFF;

    printf ("a %x b %x c %x i %x j %x k %x\n", a, b, c, i, j, k);
}

int main (void) {
    while (true) {
        scanf ("%i", &offset);
        function (1, 2, 3);
    }
}
