import time

class I(object):
    def __init__(self, value) :
        self.value = value

    def __lt__(self, other):
        return int(self.value) < int(other.value)

    def __repr__(self) :
        return self.value

ls = [I(str(x)) for x in reversed(range(1000000)) ]
start = time.time()
ls.sort()
print("took %s seconds" % (time.time() - start))

ls = list(reversed(range(1000000)))
start = time.time()
ls.sort()
print("took %s seconds" % (time.time() - start))
