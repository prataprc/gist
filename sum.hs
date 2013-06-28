sum:: [Int] -> Int
sum []     = 0
sum (x:xs) = x + (sum xs)

length:: [a] -> Int     -- type scheme
length []     = 0
length (x:xs) = 1 + (length xs)

