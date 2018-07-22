message = 'In scope'

def scopefunction() :
    global message
    message += ' In scopefunction'
    print message


class C( object ):
    _clsvar = 10

    def __init__( self, val ):
        print self._clsvar
        self._clsvar = val
        print self._clsvar, C._clsvar

c = C(20)
