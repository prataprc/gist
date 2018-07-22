#! /usr/bin/python 

# Some examples using the looping constructs in python

a = ['cat', 'dog', 'elephant']

x = 10
print type(x)

for x in a :
    print x, type(x), len(x)

b = 'hello \n world'
for x in b :
    print x, type(x), len(x)

# Dangerous iteration on a mutable sequence (list)
# for x in a :
#    a.insert(1, x)      # Dont do this !
#    print a

# To acheive the above mentioned purpose do the following
for x in a[:] :         # Now we taking a copy of the sequence
    a.insert(0, x)      # you can safely do this !
    print a

# Using the range() function
for x in range(10,100,30) :
    print x,
else
    print "the loop normally exited"
