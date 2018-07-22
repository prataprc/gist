#! /usr/bin/env python

import sys
import os

def func( *args, **kargs ) :
    for a in args :
        print "argument ", a
    for k in kargs :
        print "Keyword ", k

args = [(1,2), (2,3)]
func( *{'a':'hello', 'b':'world'} )
