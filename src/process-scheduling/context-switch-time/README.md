# Context Switch Time

The examples serve to illustrate the overheads associated with context switch.
At the core, both examples use a ping-pong pattern between two semaphores,
at minimum this should perform two context switches for each ping-pong
round.

The `simple-context-switch-time` example only does the ping-pong,
the time per ping-pong round should therefore closely approach
that of a pair of context switches.

The `context-switch-cache-flush` example performs a random memory walk
in addition to the ping-pong, set up in a way that emphasizes memory
access latency. The two threads compete for the cache capacity,
the context switch overheads will therefore include time
needed to (re)populate the cache, spread across thread
execution.

## Running the example

Bind to single processor to focus on local context switch timing.
The `perf` utility can be used to check that context switches
do happen, but requires root account privileges otherwise
0 is shown.

```
./make
taskset 1 ./simple-context-switch-time.executable
su -c "taskset 1 perf stat -e context-switches ./simple-context-switch-time.executable"
```

Experiment with various memory walk settings to see various degrees of impact.
The exact sizes may need tuning to fit your particular processor caches.

```
./make
# Single cache line accessed repeatedly
taskset 1 ./context-switch-cache-flush.executable 1000000 64
# Most L1 cache lines accessed repeatedly
taskset 1 ./context-switch-cache-flush.executable 100000 24576
# Most L1 cache lines accessed once
taskset 1 ./context-switch-cache-flush.executable 1 24576
# Most LLC cache lines accessed repeatedly
taskset 1 ./context-switch-cache-flush.executable 1000 2097152
# Most LLC cache lines accessed once
taskset 1 ./context-switch-cache-flush.executable 1 2097152
```
