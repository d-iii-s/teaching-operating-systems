# Large Heap Time

The example should provide a simple way to observe collection times on large heaps.

## Running the example

Just `javac Example.java` and `java Example` with specific heap size settings,
for example `java -verbose:gc -Xms128G -Xmx128G -XX:+UseParallelGC Example`.
