factorial 0 = 1
factorial n = n * factorial (n-1)

average [] = error "empty list"
average xs = (fromIntegral (sum xs)) / (fromIntegral (length xs))
             -- fromInteger converts Int to Float

ldf k n | (rem n k) == 0 = k
        | k^2 >= n       = n
        | otherwise      = ldf (k+1) n

factors n = 1 : p : factors (div n p)
            where p = ldf 2 n

isprime n = factors n == [1,n]

primes n = [ x | x <- [2..n], isprime x ]

fibonacci 0 = 0
fibonacci 1 = 1
fibonacci (n + 2) = fibonacci n + fibonacci (n+1)
