# Various Memory Allocation Examples

## Memory Corruption Patterns

The example implements multiple memory corruption patterns, used
to demonstrate how various memory corruption detection tools work.

## Simple Allocation Speed

Allocates and frees a given count of blocks of constant size.
Can illustrate time overhead, however,
one has to bear in mind that this is
the simplest possible workload !

## Random Allocation Speed

Allocates and frees a given count of blocks of random size.
This is a variation on the previous example with somewhat
more complex workload, however, it still does not use
concurrency !
