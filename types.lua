--> string
print(type("Hello world"))
print('Hello world')
print([[multiline string hello
world]])
print([==[
multiline string with stuffed assignment hello
world]==])
print(10 .. "20") -- automatic convertion

--> number
print(type(10.4*3))
print(4, 0.4, 4.57e-3, 0.3e12, 5e+20)
print(10 + "20") -- automatic convertion

--> boolean
-- * conditionals consider both false and nil as false and anything else as true.
-- * Beware that lua considers both zero and the empty string as true in
--   conditional tests.
print(type(true), type(false))

--> nil
-- lua uses nil as a kind of non-value, to represent the absence of a useful
-- value.
print(type(nil))

--> function
print(type(print))
print(type(type))

--> string
print(type(type(X)))

--> table
table = {}      -- table constructor
table["a"] = 10
print(table.a)  -- record syntax
table.a = nil   -- delete "a" from table
array = {}
array[1] = 10   -- as a convention arrays start with index 1
array[-1] = 20  -- can also have negative indices.

print(a[#a])    -- prints the last value of list ’a’
a[#a] = nil     -- removes this last value
a[#a+1] = v     -- appends ’v’ to the end of the list

a = {}
-- any non-initialized index results in nil; Lua uses this value as a sentinel
-- to find the end of the array.
a[10000] = 1
print(#a)       --> 0
a[1] = 2; a[2] = 3
print(#a)       --> 2

--> function
-- first-class citizen
-- nested functions and lexical scoping
-- can call functions written in C and lua

--> userdata
-- any arbitrary C data that can be stored in lua variables
-- assignments and equality tests
