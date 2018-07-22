module Main ( docmd, one, two, three ) where

import System.Environment (getArgs)

data Result a = Out a

instance Show a => Show (Result a) where
  show (Out a) = "Out " ++ show a

one x = Out x
two x = Out x
three x = Out x

docmd :: (Num t, Show t) => [ String ] -> Result t
docmd ("1":[]) = one 10
docmd ("2":[]) = two 10
docmd ("3":[]) = three [10, 20]

main = do
    args <- getArgs
    let (Out x) = docmd args
    print x
