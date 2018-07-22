#! /usr/bin/env python

import os
from   multiprocessing import Process

def info() :
    print __name__
    print os.getpid(), os.getppid()

def f(name):
    info()
    print 'hello', name

def main() :
    p = Process( target=f, args=('bob',) )
    p.start()
    p.join()
    info()

if __name__ == '__main__' : 
    main()

