# File Access Mode

The example counts how many files in the system were
accessed using the `mmap` syscall and how many using
the `read` and `write` syscalls.

## Running the example

Just run `bpftrace counter.bt` as root.
