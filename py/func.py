#! /usr/local/bin/python
import os

def func(arg1, arg2, *args, **kargs) :
    print arg1, arg2
    for arg in args :
        print arg
    for k in kargs :
        print k, ":", kargs[k]

a = (1,2,3)

func(a)
