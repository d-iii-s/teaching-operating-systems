# Stack Memory Allocation Examples

This is a collection of examples that illustrate stack allocation behavior on trivial program images.

## Simple Stack Addresses

Print addresses of local variables.
The distance between the individual addresses illustrates the stack frame size.
It is also useful to see how the compiler optimization level impacts the stack allocation behavior.

## Simple Stack Recursion

Shows how recursion uses the stack.
Optimization again also interesting.

## Control Flow Corruption

Writing into stack frame to illustrate potential for control flow corruption.
Exact behavior again depends on the compiler optimization level,
the control flow corruption effect aims at no optimization.

## Hit Stack Variable

Writing into stack frame at interactively entered offsets.

## See Stack Growth

Stack overflow with memory map dump.
Shows how the stack block grows on demand.
