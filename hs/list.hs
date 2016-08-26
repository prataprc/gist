pairs xs = zip xs (tail xs)

sorted xs = and [ x <= y | (x, y) <- pairs xs ]

positions x xs = [ i | (x', i) <- zip xs [0..n], x == x' ]
                 where n = (length xs) - 1

qsort [] = []
qsort (x:xs) = qsort smaller ++ [x] ++ qsort larger
               where
                    smaller = [a | a <- xs, a <= x ]
                    larger = [b | b <- xs, b > x ]

insert x [] = [x]
insert x (y:ys) | x <= y    = x : y : ys
                | otherwise = y : insert (x:ys)

isort (x:xs) ys = isort xs (insert x ys)
