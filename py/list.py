#! /usr/bin/python

# Lists are compound data types used to group primitive types.
# Unlike the strings which are immutable, it is possible to 
# mute list elements.

import sys

l = ['spam', 'egg', 100, 1234]

print l 
print "0th element", l[0], "3rd element", l[3], "-1th element", l[-1],
                            # Note the comma at the end ...
print "-4th element", l[-4]
print "0 to 3", l[:4]
print "-4 to -1", l[-4:-1]  # This wont print the last element
print "-4 to -1", l[-4:]    # But this would print the last element

# Repeating list elements
print l[1:-1]
print 3*l[:3] + ['Boo!']# The catch is the [] notation, python takes it as
                        # a list.
print 3*l[0] + 'Boo!'   # Without [] the data is taken as string type.

# Muting the elements.
l[2] = l[2] + 23
print l

# Replace a bunch of elements in one shot
print "Replace elements"
l[0:2] = ['Rspam', 'Regg']
print l
# Replace an element with an array of element
l[1] = ['0', '1']
print l

# Remove elements
l[0] = []
print l
l[0:2] = []
print l

# Insert elements
print "Inserting elements"
l[1:1] = ['dummy']
print l
l[1:1] = ['spam', 'egg']
print l

# Insert a copy of itself at the beginning
l[:0] = l
print l

# Clear the entire list
l[:] = []
print l

# print the list sorted
m = ['hello', 'boss']
m.sort()
print m
