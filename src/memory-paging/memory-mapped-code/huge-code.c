#include <stdio.h>
#include <stdbool.h>

int main (void) {
    int i = 0;

    while (true) {
        asm (
            ".rept 1000000000\n\t"
            "nop\n\t"
            ".endr\n\t"
        );
        printf ("Loop %i.\n", i);
        i ++;
    }

    return (0);
}
