#! /usr/bin/env python

import cPickle

a = 'hello'
b = 'world'

fd  = open( 'pickldb', 'wb' )

cPickle.dump( a, fd )
cPickle.dump( b, fd )

fd  = open( 'pickldb', 'rb' )

b = cPickle.load( fd )
a = cPickle.load( fd )

print b
print a
