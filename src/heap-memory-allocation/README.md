# Heap Memory Allocation Examples

This is a collection of examples that illustrate heap allocation behavior on trivial program images.

## Simple Allocation Overhead

Print distance between two consecutive heap allocations for different allocation sizes.
In some conditions, this can be used to estimate allocation overhead associated
with particular allocation sizes.

The script builds executables linked to different allocators (if available).
