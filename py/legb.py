#! /usr/bin/python

a = "a_in_module"
b = "b_in_module"

def func1():
    c = "c_in_func1"
    def func2() :
        global b

        b = "b_in_func2"
        print a, b, c
    b = "b_in_func1"
    print a, b
    func2() 
    return func2
