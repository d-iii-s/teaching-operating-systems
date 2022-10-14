# Memory Corruption

The example implements multiple memory corruption patterns, used to demonstrate
how various memory corruption detection tools work. The name of each executable
describes the memory corruption pattern.

## Analyzing the example

Before running the individual executables, state what you think should happen.
Each of the memory corruption patterns has the potential to crash the program,
but only some do here. Consider for how long the failure can remain
undetected, and whether the failure can even be silently remedied.

## Running the example

With no error checking, just run the given executable.
With error checking `malloc`, use `MALLOC_CHECK_=3 ./executable`.
With `memcheck` tool from `valgrind`, use `valgrind ./executable`.
