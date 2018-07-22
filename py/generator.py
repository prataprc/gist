#! /usr/bin/env python

def compare_item( a, b ) :
    return a == b

def compare_items(a, b) :
    for i in range(len(a)) :
        yield compare_item( a[i], b[i] )

a = [ 0,1,2,3,4]
b = [ 0,2,1,3,5]
for s in compare_items( a, b ) :
    print s
