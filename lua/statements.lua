-- assignments
a = 10

-- multiple assignments
a, b = 10, 10.5
a, b = b, a         -- swap to variables
a, b, c = 10, 20    -- `c` is `nil`
a, b = 40, 50, 60   -- `60` is ignored.

-- local variable declaration
x = 10
local i = 10    -- local to the chunk
while i <= x do
    local x = i*2   -- local to the while body
    print(x)
    i = i + 2
end

-- do end blocks
do
    local i, x = 0, 20    -- local to the do...end block
    while i < x do
        print(i)
        i = i + 1
    end
end

-- `if` control structures
if true then
    print("run if true")
elseif true then
    print("run if true")
else
    print("run on default case")
end

-- `while` control structures
while true do
    print("infinite loop")
end

-- `repeat` control structures
repeat
    err = print("execute atleast once")
until err ~= nil
    -- scope of the local variables declared inside the looping block is
    -- visibile to the loop-condition

-- `for`, numeric for, control structures
exp1, exp2, exp3 = 1, 20, 1
for var=exp1,exp2,exp3 do   -- numeric for loop
    print(var)
end
    -- `exp3` is optional, and when absent assumed as `1`
    -- if `exp3` is math.huge, loop does not assume an upper limit
    -- `var` is a local variable to the `for` block

-- `for`, generic for, control structures
a = {"mon", "tue", "wed", "thu", "fri", "sat", "sun"}
for k in pairs() do       -- generic for loop
    print(k)
end

-- `break` statement
-- break the inner loop defined by for, while and repeat statements

-- procedure calls

-- `return`
-- there is an implicit return for every function, returns `nil`.
