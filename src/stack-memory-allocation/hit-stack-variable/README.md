Note that the ordering of local variables on the stack is quite fragile,
in particular, taking an address of a variable may impact ordering.
As it is, the example should use a straightforward stack layout,
with `i`, `j`, `k` placed next to each other in this order.
