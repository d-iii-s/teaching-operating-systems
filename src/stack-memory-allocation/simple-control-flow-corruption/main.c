#include <stdio.h>

long *temp_one;
long *temp_two;

void three (long i) {
    printf ("function three (%li) entered\n", i);
    *(temp_two - 2) = *(temp_one - 2);
    printf ("function three (%li) leaving\n", i);
}

void two (long i) {
    printf ("function two (%li) entered\n", i);
    temp_two = &i;
    three (i + 1);
    printf ("function two (%li) leaving\n", i);
}

void one (long i) {
    printf ("function one (%li) entered\n", i);
    temp_one = &i;
    two (i + 1);
    printf ("function one (%li) leaving\n", i);
}

int main (void) { one (1); return (0); }
