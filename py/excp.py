#! /usr/bin/env python 

import sys

class MyException( Exception ) :
    pass

class MyException1( Exception ) :
    pass

def func( str ) :
    raise Exception( str )
    raise MyException( 10, str )


try :
    func( "hello" )
    print "world"
except ZeroDivisionError :
    print "Exception !!"
except MyException, (errno, err) :
    print type(err)
    print errno, "MyException ('%s')" % err
except MyException1,  err :
    print type(err)
    print "MyException1 ... ('%s')" % err
except :
    print "Catch all %s" % list(sys.exc_info())
