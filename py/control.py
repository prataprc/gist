#! /usr/bin/python 

# Some examples to use the control flow statements.

x = int(raw_input("Please enter an integer : "))
y = float(raw_input())
print x, y

if x < 0 :
    x = 0
    print "Negative changed to Zero"
elif x == 0 :
    print "Zero"
elif x == 1 :
    print "Positive"
elif x > 1 :
    print "More"
