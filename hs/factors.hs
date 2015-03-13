factors n 
    | n < 1     = error "argument not positive"
    | n == 1    = []
    | otherwise = p : factor (div n p)
                  where p = ld n
