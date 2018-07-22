#! /usr/bin/env python

import random

samplespace = 'abcdefghijklmnopqrstuvwxyz0123456789'
words      = []
total_intr = 0
intr_count = 0
min        = 100000000000000
max        = 0
count      = 100000
while count :
    word  = ''.join( [random.choice(samplespace) for i in range(6)] )
    if word in words :
        idx = words.index(word)
        words.pop(idx)
        intr = len(words) - idx
        if intr < min :
            min = intr
        if intr > max :
            max = intr
        total_intr += intr
        intr_count += 1
        print "match intr : %d, intr_count : %d, average : %f" % \
              (total_intr, intr_count, (total_intr / float(intr_count)))
    words.append(word)
    count -= 1
print "min : %d, max : %d" % (min, max)
