# Assembly Language Program Image Examples

This is a collection of examples that illustrate various assembly language features on trivial program images.

## Empty Main

Nothing except for a return statement.
Contains a standard stack frame and an integer return value.
Also illustrates some directives that the compiler sprinkles throughout the code.

## Static Global

Addressing static variables.
Illustrates difference between `.bss` and `.data` sections.
Also shows how the compiler can choose more ways to compile the same construct, here `add` vs `lea`.

## Constructed Global

Initializing static variables.
Also shows name mangling for objects.

## Empty Loop

Control flow with loop.
Examine the dump to see how variable addresses remain undefined until link time.

## Allocation Function

Simple allocation function.
Shows various types of process memory content.
