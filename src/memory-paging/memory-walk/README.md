# Memory Walk Effect

The example serves to illustrate the overheads associated with various cache levels.
At the core, the example performs a random walk through memory, with configurable
loop count, step count, and step size.

## Running the example

Bind to single processor to avoid context switch effects.
Experiment with various memory walk settings to see
various degrees of impact.

The exact sizes may need tuning to fit your particular processor caches.

```
./make
# Single cache line accessed repeatedly
taskset 1 ./memory-walk.executable 1000000000 1 64
# Many L1 cache lines accessed repeatedly
taskset 1 ./memory-walk.executable 2000000 500 64
# Many LLC cache lines accessed repeatedly
taskset 1 ./memory-walk.executable 10000 10000 64
# Most TLB entries trashed
taskset 1 ./memory-walk.executable 10000 10000 4096
```
