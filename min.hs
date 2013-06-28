-- Find smallest integer from a list.
minInts :: [Int] -> Int
minInts []     = error "empty list"
minInts [x]    = x
minInts (x:xs) = min x (minInts xs)
