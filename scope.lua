-- global and local scope
x = 10
local i = 10    -- local to the chunk
while i <= x do
    local x = i*2   -- local to the while body
    print(x)
    i = i + 2
end

-- scope blocks
--
--    while expr do end
--    repeat until expr
--    for var=expr1,expr2,expr3 do end
--    for x,y,z=expr do end
--    function end
--    do end
--
-- scope of the local variables declared inside the looping block is
-- visibile to the loop-condition
--
-- control variable created/initialized in the for .. end block is local to
-- the block

-- create an local scope using do ... end block
do
    local i, x = 0, 20    -- local to the do...end block
    while i < x do
        print(i)
        i = i + 1
    end
end


print(b)  -- uninitialized variable emit `nil`
b = 10    -- Initialized as global variable, no special declaration needed
print(b)  -- 10
b = nil   -- delete a gobal variable
