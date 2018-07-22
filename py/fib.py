#! /usr/bin/python

class c:
    def __init__(self, var) :
        self.a = var

my_c = c(10)

def fib(n) :
    """ print a sequence of fibonacci series """
    a, b = 0, 1
    result = [b]
    while b < n :       # Like C, any non ZERO value is TRUE.
                        # Unlike C, strings, list, sequence can also be 
                            # used, where FALSE means it is empty.
        a, b = b, a+b   # The expression on the RHS are evaluated first from
                            # left to right

        result.insert(len(result), b)
        # result.append(b)  # same as above and does, result = result + [b]
    print my_c.a
    my_c.a=20
    print my_c.a

    return result 

n = 2000

print fib(10)
