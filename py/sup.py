#! /usr/bin/env python3.2

class Base( object ):

    def __init__( self, *args ):
        print( "Base init", self, *args )

    @classmethod
    def fun1( cls, *args ):
        print( "Base", cls, *args )

    @staticmethod
    def fun2( *args ):
        print( "Base", *args )

    def fun3( self, *args ):
        print( "Base", self, *args )

class Derived( Base ):

    def __init__( self, *args ):
        super().__init__( *args )
        print( "Derived init", self, *args )

    @classmethod
    def fun1( cls, *args ):
        super().fun1( *args )
        print( "Derived", cls, *args )

    @staticmethod
    def fun2( *args ):
        print( "Derived", *args )

    def fun3( self, *args ):
        super().fun1( *args )
        print( "Derived", self, *args )

o = Derived()
o.fun1( 10 )
o.fun2( 20 )
o.fun3( 30 )
