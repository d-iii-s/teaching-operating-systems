# Why Not Finalizers

The example should illustrate why using finalizers is potentially risky.
Intuition suggests objects should not be collected why their methods
are running, but the example shows exactly that happening.

## Running the example

Just `javac Example.java` and `java Example`.

## Analyzing the example

Try to run with `-XX:+PrintCompilation` to understand what is happening.

When the loop is iterated enough times, JIT is triggered. The native
version of `work` does not need a reference to `this`, so it is
optimized away, and when the native version replaces the
interpreter via OSR, the garbage collector will collect
the `Example` object instance.

## References

Adopted from https://stackoverflow.com/a/26645534/345436.
