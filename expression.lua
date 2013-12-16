-- string literals
s = "string"
s = 'string'
s = [[
multi
line
string]]
s = "汉语 or 漢語, Hànyǔ"

-- numberic constants
i = 4
i = 0.4
i = 4.57e-3
i = 0.3e12
i = 5e+20

-- unary operations
neg = -10

-- binary operations
a = 10 + 29.9
a = 90 - 80
a = 9  * 3
a = 9  / 3
a = 10 ^ (-1/2) -- inverse square root
a = 11 % 2 --> equivalent of `11 - floor(11/2) * 2`
        -- for integer arguments module has same sign as the second argument.

x = math.pi
y = x % 1       -- 0.14159265358979 factional part
y = x % 0.01    -- 0.00159265358979
y = x - x%1     -- 3 integer part

-- relational operators
x = 10 == 10
x = 10 ~= "10"
    -- if values have different types, then they are not considered equal
    -- table, userdata, function are compared using reference
    -- nil is equal only to itself
x = 10 < 20
x = 10 <= 10
x = 20 > 10
x = 10 >= 10
    -- order operation is applicable only to two numbers or two strings

-- logical operators
x = not (true and false or true)
    -- both `and` `or` operators use short-circuit evaluation

-- concatenation operator
print("hello" .. "world")
print("hello" .. 123)
print(0 .. 123)
    -- automatic type convertion, numbers are converted to string

-- length operator
a = {}
s = "hello world"
print("length of table", #a, ". length of ", s, #s)

-- precedence
--      ^
--      not # - (unary) * / %
--      + -
--      ..
--      < > <= >= ~= == and
--      or
-- all binary operators are left-associative
-- except for `^` and `..` which are right associative
--     a+i < b/2+1      <--> (a+i) < ((b/2)+1)
--     5+x^2*8          <--> 5+((x^2)*8)
--     a<y and y<=z     <--> (a<y)and(y<=z)
--     -x^2             <--> -(x^2)
--     x^y^z            <--> x^(y^z)

-- table constructors
days = {"mon", "tue", "wed", "thu", "fri", "sat", "sun"}
print(days[1])  --> "mon"
days = {[0] = "mon", "tue", "wed", "thu", "fri", "sat", "sun"}
                -- to start the list with `0` index
t = {x=10, y=20}
print("initialized table constructor", t.x, t.y)
opnames = {["+"] = "add", ["-"] = "sub", ["*"] = "mul", ["/"] = "div"}

-- values in conditionals
if false then print() else print("false is false") end
if nil then print() else print("nil is false") end
if "string" then print("anything else is true") else print() end
if "" and 0 then print("even empty string and zero is true") else print() end

-- no automatic conversion in conditionals
if 10 == "10" then print() else print("no automatic conversion") end
