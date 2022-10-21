#!/usr/bin/env python

import sys

def get_full_list ():
    a = object ()
    b = object ()
    c = object ()
    l = [a, b, c]
    return l

def print_ref_count (l):
    print (sys.getrefcount (l))
    print (sys.getrefcount (l[0]))

l = get_full_list ()
print_ref_count (l)
