m :: (Num a) => ([a],[a],[a]) -> ([a],[a],[a])
m (h:f, u, t) = (f, u, h:t)

a :: (Num a) => ([a],[a],[a]) -> ([a],[a],[a])
a (f, t, u) = (f, u, t)

b :: (Num a) => ([a],[a],[a]) -> ([a],[a],[a])
b (f, u, t) = (u, f, t)

c :: (Num a) => ([a],[a],[a]) -> ([a],[a],[a])
c (u, f, t) = (f, u, t)

h :: (Num a) => a -> ([a],[a],[a]) -> ([a],[a],[a])
h 1 (f, u, t) = m (f, u, t)
h n (f, u, t) = c (h (n-1) (b (m (a (h (n-1) (f, t, u)) ))))

hanoi :: (Num a) => a -> [a] -> ([a],[a],[a])
hanoi n l = h n (l, [], [])

main = print (hanoi 23 [1..23])
