infix ==>
infix <=>
infix <+>

--conjunction
True && x  = x
False && x = False

--disjunction
True || x = True
False || x = False

--negation
not True = False
not False = False

--implication, converse and contraposition ??
True ==> x = x
False ==> x = True

--equivalence, if x => y and y => x
x <=> y = x == y

--exclusive OR, same as ! <=>
x <+> y = x /= y
