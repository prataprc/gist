-- Demonstratrate composing arithematic expression in Haskell
--
-- Some of the standard modules,
--      Prelude : pi, exp, putStrLn
--      System
--      
-- Interpreter commands
--      :?
--      :module + Mod
--      :load ProgFile
--      :type
--      :set prompt promptname
--      :info (operator)
--      :set +t
--      :cd Path
--
-- Bool,
--      Infering True or False from other data type is not implicit.

add  a b = a + b     -- Add, can also be written as, (+) a b, prefix
sub  a b = a - b     -- Subract
mult a b = a * b     -- Multiply
divd a b = a / b     -- Divide
ipow b e = b ^ e     -- Base 'b' power 'e' (integer version)
dpow b e = b ** e    -- Base 'b' power 'e' (float version)
neg  a   = (-a)      -- Better to enclose negation in paranthesis

and  a b = a && b    -- Logical AND
or   a b = a || b    -- Logical OR, short circuits evaluation
lnot a   = not a     -- Logical NOT

eq   a b = a == b    -- Comparison EQUAL
ne   a b = a /= b    -- Comparison NOT-EQUAL
lt   a b = a < b     -- Comparison LESS-THAN
le   a b = a <= b    -- Comparison LESS-THAN-EQUAL
gt   a b = a > b     -- Comparison GREATER-THAN
ge   a b = a >= b    -- Comparison GREATER-THAN-EQUAL

e        = exp 1     -- 

sqrt     6
succ     7
succ     7.1
pred     8.2
sin      pi/2
truncate pi
round    3.5
round    3.4
floor    3.7
ceiling  3.3
odd      3

-- List Data type, is a polymorphic datatype (parametrized type)

list_i   = [ 0, 1, 2, 3 ]         -- List of Homogenous elements
list_s   = [ "hello", "world" ]
list_ie  = [ 0..10 ]              -- List of integers using enumeration notation
list_iei = [ 1, 1.25 .. 10 ]      -- List of integers using enumeration notation
                                  --   with increment value
list_ie1 = [ 1, 4 .. 15 ]         -- Last element of the list will be 13.
list_ied = [ 10, 9 .. 1 ]         -- List of integers using enumeration notation
                                  --   with decrement value

lconcat l1 l2 = l1 ++ l2          -- Concatenate 2 lists
lcons   e, l  = e : l             -- List Construct with head 'e' and tail list 'l'

head [x:xs]  = x                  -- Return the first element in the list
tail [x:xs]  = xs                 -- Return remaining element in the list
lastButOne xs= reverse xs !! 1

take 3, [1,2,3,4]                 -- Return first `n` elements of list
drop 3, [1,2,3,4,5]               -- Return all but first `n` elements of list
lines "hello\nworld"              -- split line into lines on line boundaries
last [1,2,3,4]                    -- Return last element of list

-- Tuple Data type

tup_1    = (1964, "Labyrinths")   -- Tuple of Heterogenous elements, a tuple's type
                                  --   represents the `number`, `position` and
                                  --   `type` of its elements.
tup_2    = ()                     -- special case, similar to `void`
tup_3    = (1)                    -- Invalid, no notion of one-element tuple
fst tup  =                        -- Return first element in the 2-tuple
snd tup  =                        -- Return second element in the 2-tuple

-- Strings, are essentially 'list data-type' with Char elements

ch       = 'a'
str      = "Hello world"
seql     = "" == []               -- This returns True, since String is List

-- Type system

ch1      = 'a'  :: Char           -- Type signature
-- Type variable always start with a lowercase letter.

-- Functions
--  * A function is a single expression, not a sequence of statements.
--  * `=` implies meaning of a function / variable not assignment, and once
--    defined its meaning cannot be changed.
--  * `if` keyword is also an expression with its syntax,
--          if Bool then exp-type else exp-type
--     both branches of if should be of same type, which will be the type of
--     if expression itself.

myDrop n xs = if n <= 0 || null xs
              then xs
              else myDrop (n-1) (tail xs)


-- Notes :
--
--  1. Spaces can some-times be significant. Since Haskell allows us to define
--     operators, EG, for 2*-4, Haskell will parse it as '*-' operator.
--
--  2. Using enumeration notation over floating point numbers can pack more
--     than a few surprises, so if you use it at all, be careful. Floating
--     point behavior is quirky in all programming languages; there is nothing
--     unique to Haskell here.
--
--  3. Indentation is important : it `continues` an existing defintion, instead
--     of starting a new one.
--
--  4. Operators are not special, they are not built into the language and new
--     operators can be defined by the programmer.
