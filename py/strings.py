#! /usr/bin/python

print "Hello, World"
print 'Hello, World'
print '"Hello", World'
print """ Just print 
me as is ...
    including the tab ...
    or spaces ....
    """
print "Hello", "world"

# string literals spanning multiple lines.
str1 = "Hello,\
        World"
str2 = "Hello \n\
        world"
str3 = r"Hello\n\
        world"

# concatenating string literals
print "Hello" + "World"
print "Hello" "World"   # This applies only for two string literals
print 'Hello' 'World'   # This applies only for two string literals

# Repeating strings
str4 = "Hello" + "World" * 5
print str4
str5 = ("Hello" + "World") * 5
print str5
print "Hello" * 5 + "World"
print "Hello" "world" * 5
print ("Hello" "world") * 5

# Stripping strings
print "Hello".strip()
print "Hello".strip("Ho")
print "Hello".strip("elo")
print str4.strip("World")

# string as an array of character and slice notation
i = 0
while i < 10 :
    print i, str4[i]
    i = i + 1

print "In reverse"
i = -len(str4)
while i < 0 :
    print i, str4[i]
    i = i + 1

# Slice notation
i = 0
while i < 10 :
    print i, str4[0:i], str4[i:30]
    i = i + 1

i = -len(str4)
while i < 0 :
    print i, str4[i:30], str4[0:i]
    i = i + 1
