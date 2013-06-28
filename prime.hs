prime n | n < 1     = error "not a positive integer"
        | n == 1    = False
        | otherwise = (ldf 2 n) == n

ldf k n | (rem n k) == 0 = k
        | k^2 >= n       = n
        | otherwise      = ldf (k+1) n
