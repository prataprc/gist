#! /usr/bin/env python3.2

import sys, io, traceback

def print_exc() :
    """Return a string representing exception info."""
    typ, val, tb = sys.exc_info()
    f = io.StringIO()
    traceback.print_exception( typ, val, tb, file=f )
    s = f.getvalue()
    f.close()
    return s

try:
    mixer()
    f = open('myfile.txt')
    s = f.readline()
    i = int(s.strip())
except IOError as err:
    print(err.errno)
    print("I/O error: {0}".format(err))
except ValueError:
    print("Could not convert data to an integer.")
except:
    print( print_exc() )

