#! /usr/bin/python
i = 0
while i <= 255 :
    print "%4d %2x %4c" % (i, i, i),
    if (i % 8) == 0 : 
        print
    i += 1
