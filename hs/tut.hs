--------------- About interpreter
--  :?  - help
--  :set prompt "<promptname>"
--  :set +t
--  :module <modulename>
--  :info
--  :type
--  let
--      ghci's `let` is not same as `let` for defining local variables.
--  it
--      value of the last expression evaluated.
--  Prelude 
--      a standard library of useful functions.
--  :unset
--      Complement of `:set`


-- Spaces and tabs :
--      Most of the time we can omit white spaces in expression, and but not
--        always. Eg, exression `2*-3` will parsed for operator `*-`.


--------------- Data types
-- Integer :
--      Arbitrarily large.
--
-- Atoms (not an official nomenclature) :
--      True - Boolean true.
--      False - Boolean false.
--
-- Notes :
-- 1. Date Type names,
--      Integer, String, [Char],
--      Ratio Integer (from Data.Ratio module)
-- 2. Inferring Boolean, Other data values are "not automatically" inferred to
--    boolean values based on the context.
-- 3. Haskell requires that type names to start with UPPERCASE and variable
--    names to start with lowercase.
-- 4. For Type name, String == [Char] evaluates to True


--------------- Compound data types
-- List :
--      All elements of a list must of same type.
--      Enumerating floating point numbers can sometime throw up surprises due
--        to roundoff problems.
--  Eg,
--      [] Empty list.
--      [1,2,3] List of integers.
--      [1..20] Enumerated list of integers, with closed interval.
--      [1, 1.25 .. 2.0 ] Enumerated list with increment value
--      [1..] Infinite list
--
-- List Operations,
--      [3,1,3] ++ [3,7] List addition
--      1 : [2,3] List construction
-- 
-- String :
--      Sequence of characters are enclosed with double-quotes.
--          Eg, "hellow world"
--      Single character are enclosed with single-quotes.
--          Eg, 'w'
--      String is nothing but a "List of characters"
--


--------------- Functions
-- 1. Function calls don't need parantesis
--      Eg, exp 1 is same as exp(1)


myDrop n xs  = if   n <= 0 || null xs
               then xs
               else myDrop (n - 1) (tail xs)

isOdd n      = (mod n 2) == 1

data BookInfo     = Book Int String [String]
                    deriving (Show)

data MagazineInfo = Magazine Int String [String]
                    deriving (Show)
