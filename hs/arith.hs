add a b      = a + b
addinfix a b = (+) a b 
mult a b     = a * b
div a b      = a / b
neg a        = (- a)       -- The only unary operator in haskell
addneg a b   = a + (-b)    -- Cannot be mixed with infix operators,
                           --   must be enclosed with paranthesis, like, (-3).
intexp b e   = b ^ e
floatexp b e = b ** e

-- While some programming languages treat the number zero as synonymous
-- with False, Haskell does not, nor does it consider a non-zero value to be
-- True.

eq a b      = a == b
ls a b      = a < b
gt a b      = a > b
lseq a b    = a < b
gteq a b    = a > b
ne a b      = a /= b            -- (In C it would be != )
true x      = x == True
false x     = x == False

and a b     = a && b
or a b      = a || b
mynot a b     = not b

main = print (add 10 20)
