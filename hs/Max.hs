mymax :: Ord(a) => [a] -> a
mymax [] = error "Empty list !"
mymax [x] = x
mymax (x:xs) = max x (mymax xs)

main = print ( length [ mymax([1..1000]) | x <- [1..1000000] ] )
