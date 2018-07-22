#! /usr/bin/python 

import sys

which = raw_input("0 - use raw_input \n1 - use input \n: ")
if which == "0" :
    # Every thing is string here.
    x = raw_input("Please enter an integer : ")
elif which == "1" :
    # input() does not seem to take inputs of list type
    x = input("Please enter an integer : ") 
else :
    print "Why have you entered an invalid input ?"
    sys.exit()

print "X is : ", x, "And type of x is : ", type(x)
