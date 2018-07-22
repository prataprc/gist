def firstcall() :
    __import__( 'logging', globals(), locals(), ['getLogger'] )

def secondcall() :
    print type(getLogger)

firstcall()
secondcall()
