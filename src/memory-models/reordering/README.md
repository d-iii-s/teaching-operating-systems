# Memory Operation Reordering

The example investigates whether memory operation reordering can lead to sequentially inconsistent results.
The operations represent the canonical example of two threads executing `X=1 ; READ (Y)` and `Y=1 ; READ (X)`,
the two threads are synchronized to execute the code simultaneously, and another thread tallies counts of
individual results, including the `X == 0 ; Y == 0` result, impossible with sequential consistency.

## Running the example

```
./make
./count-weird-results.executable
```

Since there are three threads actively waiting, a machine with at least three logical processors is useful.
