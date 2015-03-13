average:: [Int] -> Float
average [] = error "empty list"
average xs = fromInt (sum xs) / (fromInt length xs)
             -- fromInt converts Int to Float
