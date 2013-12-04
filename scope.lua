function scope()
    print("hello world")
end

a = 10
scope()
print(_G)
print(_ENV)
