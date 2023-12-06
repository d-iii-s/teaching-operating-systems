# False Sharing Effect

The example serves to illustrate the performance impact of false sharing.
The executable accesses two variables stored a given distance away from
each other in two threads. When the distance fits within a single
cache line and the two threads execute on different cores,
false sharing overhead is visible.

## Running the example

```
./make
# Two variables in one cache line
time ./false-sharing.executable 1
# Two variables in two non adjacent cache lines
time ./false-sharing.executable 128
```

Also try with `perf stat -e l1d.replacement`.
