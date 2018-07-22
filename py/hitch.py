def hitch( obj, cls, function, *args, **kwargs ) :
    """Hitch a function with a different object and different set of
    arguments."""
    def fnhitched( self, *a, **kw ) :
        kwargs.update( kw )
        return function( self, *(args+a), **kwargs )
    return fnhitched.__get__( obj, cls )


class O( object ):
    pass

def jbx( *args, **kwargs ):
    print( "%s %s" % (args, kwargs))

o = O()

o.jbx = hitch( o, O, jbx, 10,20, a=30, b=40 )
o.jbx( 1,2, x=3,y=4)
