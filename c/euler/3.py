#! /usr/bin/env python

import cmath
import struct
import array

number      = 600851475143
primefd     = open( 'prime.bin', 'r' )
root        = int(abs(cmath.sqrt( number ))) + 1
allprimes   = array.array( 'L' )
allprimes.fromfile( primefd, root / 3 )
def factorize( num, f ) :
    for p in allprimes :
        if p >= root :
            break
        if (num % p) == 0 :
            f.append( p )
            factorize( num / p, f )
            break
    if p > root and len(f) != 0 :
        f.append( num )
    return f

factors = []
factorize( number, factors )
print factors
