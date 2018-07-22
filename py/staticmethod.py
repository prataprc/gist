#! /usr/bin/env python
class X( object ) :
     
    @staticmethod
    def func( arg1, arg2 ) :
        print arg1, arg2

    def _get( self ) :
        X.func( "ha ha", 10 )

    a = property( _get )

x = X()
X.func( 10, 20 )
x.func( 30, 40 )
x.a
