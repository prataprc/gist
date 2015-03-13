lua -i <filename>   # load the chunk in <filename> and enter interactive mode.
lua -e "print(math.sin(12))"   # -0.53657291800043
lua -l <library> # The -l option loads a library.
??? What is the search path of the library ???

# Whenever the global variable _PROMPT is defined, lua uses its value as
# the prompt when interacting. So, you can change the prompt with a
# call like this:
lua -i -e "_PROMPT=’ lua> ’"

# In interactive mode, you can print the value of any expression by writing a
# line that starts with an equal sign followed by the expression:
> = math.sin(3)  # 0.14112000805987
> a = 30
> = a            # 30

# When the interpreter loads a file, it ignores its first line if this line
# starts with a number sign (‘#’). This feature allows the use of Lua as a
# script interpreter in Unix systems. If you start your script with something
# like
#!/usr/local/bin/lua

# Before running its arguments, lua looks for an environment variable named
# LUA_INIT. If there is such a variable and its content is @filename, then lua
# runs the given file. If LUA_INIT is defined but does not start with ‘@’, then
# lua assumes that it contains Lua code and runs it

# A script can retrieve its arguments in the global variable arg.
lua -e "sin=math.sin" script a b
# lua collects the arguments as follows:
#   arg[-3] = "lua"
#   arg[-2] = "-e"
#   arg[-1] = "sin=math.sin"
#   arg[0] = "script"
#   arg[1] = "a"
#   arg[2] = "b"
