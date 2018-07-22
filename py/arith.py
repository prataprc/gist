#! /usr/bin/python

print "Division with different signs"
print "7/-3 = ", 7/-3
print "-7/3 = ", -7/3
print "7/3  = ", 7/3
print "-7/-3= ", -7/-3
print ""

print "Modulo with different signs"
print "7%-3 = ", 7%-3
print "-7%3 = ",-7%3
print "7%3  = ", 7%3
print "-7%-3= ", -7%-3
print ""

print "Complex Numbers"
cn = 10 + 15j
print cn, "Real : ", cn.real, ", ", "Imaginary : ", cn.imag

# Another way of forming complex numbers
cn = complex(20, 10)
print cn, "Real : ", cn.real, ", ", "Imaginary : ", cn.imag
print ""

# Conversion function
f = 10.2
i = 20
i2f = float(20)
f2i = int(10.2)

print "Int   : ", i, ", " "Converted to float : ", float(i)
print "Float : ", f, ", " "Converted to int : ", int(f)

print "Length of int is ", len(i)
print "Length of float is ", len(f)
print "Length of long is ", len(long(i))
