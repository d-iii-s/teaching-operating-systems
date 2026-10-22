# Why Not Finalizers

The example illustrates a non portable use of finalizers to implement lock guards.
While the CPython runtime releases the lock guard instances on going out of scope,
the pypy runtime remains blocked.

## Running the example

Just `python example.py` or `pypy example.py`.
