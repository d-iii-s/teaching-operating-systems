#!/usr/bin/env python

import sys

a = object ()
b = object ()
c = object ()
l = [a, b, c]
print (sys.getrefcount (l))
print (sys.getrefcount (l[0]))
