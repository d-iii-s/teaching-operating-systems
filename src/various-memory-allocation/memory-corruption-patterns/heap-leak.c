#include <stdlib.h>

#define SIZE 123

int main (void) {

  // Allocate an array on heap.
  int *array = (int *) malloc (sizeof (int) * SIZE);

  // Do not release the array.
  return (0);
}
