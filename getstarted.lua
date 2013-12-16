print("Hello world")

function fact(n)
    if n == 0 then
        return 1
    else
        return n * fact(n-1)
    end
end

print("enter a number:")
a = io.read("*number")
print(fact(a))

function norm(x, y)
    return ((x^2) + (y^2)) ^ 0.5
end

function twice(x)
    return 2*x
end

-- Identifiers in Lua can be any string of letters, digits, and underscores,
-- not beginning with a digit;
--      i      j       i10      _ij     aSomewhatLongName    _INPUT
--
-- You should avoid identifiers starting with an underscore followed by one or
-- more upper-case letters (e.g., _VERSION); they are reserved for special
-- uses in Lua
