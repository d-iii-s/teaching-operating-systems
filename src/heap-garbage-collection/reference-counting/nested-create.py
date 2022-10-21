#!/usr/bin/env python

import sys

def get_full_list ():
    a = object ()
    b = object ()
    c = object ()
    l = [a, b, c]
    return l

l = get_full_list ()
print (sys.getrefcount (l))
print (sys.getrefcount (l[0]))
