#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#define BUFFER 16384

#define PERIOD 10000


void dump_maps () {
    FILE *input_file = fopen ("/proc/self/maps", "r");
    assert (input_file != NULL);
    while (true) {
        char input_buffer [BUFFER];
        char *input_line = fgets (input_buffer, BUFFER, input_file);
        if (input_line == NULL) break;
        printf ("%s", input_line);
    }
    int input_status = fclose (input_file);
    assert (input_status == 0);
}


void loop (int depth) {
    if (depth % PERIOD == 0) {
        printf ("Stack depth %i [stack]\n", depth);
        dump_maps ();
    }
    loop (depth + 1);
}


int main (void) {
    loop (0);
}
