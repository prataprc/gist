
data X = X Int deriving Show
data Y = Y Int deriving Show

class C a where
    buckle :: X -> Y -> a

instance C X where
    buckle (X a) (Y b) = X a

--instance C Y where
--    buckle (X a) (Y b) = Y b

main = do
    print $ buckle (X 10) (Y 20)
