sortInts :: [Int] -> [Int]
sortInts [] = []
sortInts xs = m : (sortInts (prune xs [m])
              where m = minInts xs
