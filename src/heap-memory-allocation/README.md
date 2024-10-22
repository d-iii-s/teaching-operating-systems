# Heap Memory Allocation Examples

This is a collection of examples that illustrate heap allocation behavior on trivial program images.

## Simple Allocation Overhead

Print distance between two consecutive heap allocations for different allocation sizes.
In some conditions, this can be used to estimate allocation overhead associated
with particular allocation sizes.

The script builds executables linked to different allocators (if available).

## Simple Allocation Sequence

Print distance between two consecutive heap allocations for growing allocation sizes.
This is a variation on the previous example that can also hint at some aspects
of the allocator implementation.

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
