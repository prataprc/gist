Y = lambda f: (lambda x: f(lambda *args: x(x)(*args)))(lambda x: f(lambda *args: x(x)(*args)))
fact = lambda f: lambda x: 1 if x == 0 else x * f(x-1)

Y(fact)(5)
