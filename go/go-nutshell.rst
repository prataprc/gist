Code blocks
-----------

Golang is a curly braced language organised in blocks of code where
every block begins with `{` and ends with `}`, except the implicit
blocks described below:

* The universe block encompasses all Go source text.

* Each package has a package block containing all Go source text for
  that package.

* Each file has a file block containing all Go source text in that file.

* Each "if", "for", and "switch" statement is considered to be in
  its own implicit block.

* Each clause in a "switch" or "select" statement acts as an implicit
  block.

Identifiers
-----------

Identifiers name program entities such as variables and types.

normal7
_ignore
ThisVariableIsExported
αβ

Operators
---------

Takes two operands of same type and return an output value of same type.

Arithmetic operators `+` `-` `*` `/` `%`

Unary operators `+` `-` `++` `--``

Bitwise Operators `&` `|` `^` `&^` `<<` `>>`

Compare Operators `==` `!=` `<` `>` `<=` `>=`

Boolean operators `&&` `||` `!`

Assignment Operators `+=` `-=` `*=` `/=` `%=` `&=` `|=` `^=` `&^=` `<<=` `>>=`

- `^` is bitwise XOR of i/p operands, unary TBD ?

- `&^` is bitwise clear (AND NOT), unary TBD ?

- `<<`, `>>` TBD logical or arithmetic ?

- Compare operators take two operands of same type and returns a boolean
  true or false.

- Boolean operators take two operands of boolean type and returns a
  boolean true or false.

(    )
[    ]
<-    {    }
=     :=    ,    ;
...   .    :

Types
-----

Integer int int8 int16 int32 int64 uint uint8 uint16 uint32 uint64

Floating float32 float64

Complex complex64 complex128

Rune rune

Boolean bool

String string

Error error

Pointer uintptr

- Integers can be represented in 8-bit or 16-bit or 32-bit or 64-bit sizes,
  either as a signed value or un-signed value.

- Signed integers are stored in 2's complement.

Reserved identifiers:
    Constants:
        true false iota

    Zero value:
        nil

    Functions:
        append cap close complex copy delete imag len
        make new panic print println real recover

Along with the following keywords:

    break        default      func         interface    select
    case         defer        go           map          struct
    chan         else         goto         package      switch
    const        fallthrough  if           range        type
    continue     for          import       return       var


Built in function
-----------------

close()

Built in function - append()
----------------------------

Variadic functions
------------------

A variadic function is a function of indefinite arity, i.e., one which
accepts a variable number of arguments.

    func sum(nums ...int) int {
        total := 0
        for _, num := range nums {
            total += num
        }
        return total
    }

    func main() {
        sum(1, 2)
        sum(1, 2, 3)
    }
