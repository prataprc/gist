data Shape a = Circle a
             | Rectangle a deriving (Eq, Ord)

data Vector a = Vector a a a deriving (Show)  

data Car a b c = Car { company :: a
                     , model :: b
                     , year :: c
                     } deriving (Show)  

type AssocList k v = (k,v)

vplus :: (Num t) => Vector t -> Vector t -> Vector t  
(Vector i j k) `vplus` (Vector l m n) = Vector (i+l) (j+m) (k+n)  
  
vectMult :: (Num t) => Vector t -> t -> Vector t  
(Vector i j k) `vectMult` m = Vector (i*m) (j*m) (k*m)  
  
scalarMult :: (Num t) => Vector t -> Vector t -> t  
(Vector i j k) `scalarMult` (Vector l m n) = i*l + j*m + k*n  

instance (Read a) => Read (Shape a) where
    readsPrec _ str = read str

cylinder :: (RealFloat a) => a -> a -> a  
cylinder r h =
    let y = 2 in sideArea + y * topArea
    where sideArea = 2 * pi * r * h  
          topArea = pi * r ^2  

tellCar car@(Car {company = c, model = m, year = y}) = car

x = 10
y = (10, "hello"):(20, "world"):[]

main = do
        print $ tellCar $ Car "aa" "bbb" 1982
