-- Example on Type constructors using `type`

data X = T { firstn, lastn :: String }

data Y a b = Y a b deriving Show

type MyY = Y Int

instance Show X where
    show x = firstn x ++ lastn x

fn :: (b -> MyY b) -> b -> MyY b
fn x b = x b

-- Example on monomorphic restriction
f :: Bool -> [ t -> ([Bool], t) ]
f x = let g y z = ([x,y], z)
      in [g True, g False]

-- The code
kI :: Int
kI = 4

kF :: Float
kF = 4

kN :: (Num a) => a
kN = 4

k = 4 / 5

main = do
    let x = T {lastn="world", firstn="hello"}
    print x
    print $ fn (Y 10) 20
    --
    print $ length $ f False
