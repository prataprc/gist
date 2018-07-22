# /usr/bin/env python3

# metaclassing Python 3.0 style

class Meta( type ):
    def __new__( cls, name, bases, d ):
        new_cls = type.__new__(cls, name, bases, d)
        print( cls, name, bases, d, sep="\n" )
        print([ x for x in new_cls.mro() ])
        print()
        return new_cls

class X( object ): pass

class A( dict, metaclass=Meta ): pass

class B( dict, metaclass=Meta ): pass

class C( B, A, metaclass=Meta ): pass
  
class D( A, B, metaclass=Meta ): pass

class E( X, metaclass=Meta ): pass

class D( E, D, metaclass=Meta ): pass

class D( C, E, metaclass=Meta ): pass

print( "mro", D.mro() )
