#! /usr/bin/env python

factors = [3, 5, 10, 2]
factors.sort()
multiples = {}
[ multiples.update([ (m, '') for m in range(f, 10000, f) if m not in multiples ]) for f in factors ]
print sum(multiples)

# Surprisingly the following algorithm work slower
#
#sum = 0
#for f in factors :
#    for m in range(f, 10000, f) :
#        for hf in factors[ factors.index(f)+1 : ] :
#            if (m % hf) == 0 :
#                break
#        else :
#            sum += m
#print sum
