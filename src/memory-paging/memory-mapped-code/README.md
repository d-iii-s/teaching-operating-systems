# Memory Mapped Code

The example shows how memory mapped files work for code,
and invites experimenting with launching multiple
processes from the same executable.

In particular, try to launch multiple processes and
observe system memory consumption.

## Running the example

Just `./make` and `./huge-code.executable`, but expect
the build process to take some time (give or take few
minutes) because the executable is quite large.

For more fun, `perf stat -I 1000 -e page-faults ./huge-code.executable` and try to explain the page fault counts.
