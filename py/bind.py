#! /usr/bin/env python

import sys

class Sample( object ) :
    def __init__( self ) :
        pass

def func( self, *args, **kwargs ) :
    print 'hello world'

o = Sample()
o.meth = func
o.meth()
