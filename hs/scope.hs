module Main
where

class Main a where 
  (.=) :: a -> a -> Bool

data Tree a = Main a | Branch (Tree a) (Tree a)  deriving Show

instance (Eq a) => Main (Tree a) where 
  Main a         .= Main b          =  a == b
  (Branch l1 r1) .= (Branch l2 r2)  =  (l1 .= l2) && (r1 .= r2)
  _              .= _               =  False

class X a where
  hello :: a -> String

data Y a = X a deriving Show

instance (Show a ) => X (Y a) where
  hello (X s) = show s

main = do
    print $ (Main 10) .= (Main 10)
    print $ hello (X "hello world")
    print $ hello (X 10)
