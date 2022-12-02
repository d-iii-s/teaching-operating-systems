# Memory Mapped Data

The example shows how memory mapped files work for data,
and invites experimenting with sharing the same file
among multiple processes.

In particular, check out the interaction between
normal and mapped versions, and consider what
that implies about the implementation of
file access.

## Running the example

Run `normal-writer.executable` first to create the file,
the start order of the other executables is arbitrary.
Use a new window for each process.

```
./make
./normal-writer.executable
./normal-reader.executable
./mapped-writer.executable
./mapped-reader.executable
```
