#include <stdlib.h>

#define SIZE 123

int main (void) {

    // Allocate an array on stack.
    int array [SIZE];

    // Write just past the end of the array.
    array [SIZE] = 0;

    return (0);
}
