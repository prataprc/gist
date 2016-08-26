prime n | n < 1     = error "not a positive integer"
        | n == 1    = False
        | otherwise = (ldf 2 n) == n
