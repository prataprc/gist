import Data.Char (ord, chr)

data TypeI = Int deriving Show
data TypeC = Char deriving Show

class TCheck m where
  (.^.) :: m -> Char -> Char

instance TCheck Int where
  x .^. y = chr (x + ord y)

-- instance TCheck Char where
--   (.^.) x y = chr (ord x + y)


main = do 
    let a = (10::Int) .^. 'x'
    print a
