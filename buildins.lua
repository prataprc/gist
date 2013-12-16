tostring(10)
tonumber("10")

table = {x=20, y=30}
for i, v = ipairs(table) do print(i,v) end
for k = pairs(table) do print(k) end
