# Deadlock

The examples just create a simple deadlock.

## Running the example

Note how `helgrind` from `valgrind` can detect the lock order violation.

```
./make
./deadlock-fast.O3.executable
./deadlock-slow.O3.executable
valgrind --tool=helgrind ./deadlock-slow.O3.executable
```
