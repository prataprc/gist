-- use elements in xs to prune ls.
prune [] xs     = []
prune ls []     = ls
prune ls (x:xs) = prune (prunex ls x) xs

prunex []     x = []
prunex (l:ls) x
    | l == x    = ls
    | otherwise = (l:(prunex ls x))
