# Reference Count

The examples illustrate the working of reference counting in Python.
Note that due to the internal mechanics of function invocation,
each function invocation increments the reference count by
two rather than one, except for `sys.getrefcount`, which
is a native function and therefore behaves differently.
