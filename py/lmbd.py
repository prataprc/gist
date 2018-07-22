import os
fn = lambda a,b : [
        f 
        for f in os.listdir('.' )
        ]

rc = 1
rb = rc and 2
print fn(0,1)
print rc, rb
