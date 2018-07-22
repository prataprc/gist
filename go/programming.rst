Variadic functions
------------------

A variadic function is a function of indefinite arity, i.e., one which
accepts a variable number of arguments.

EG: from golang

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

Divide, quotient, reminder and operand sign
-------------------------------------------


Arithematic shift and logical shift
-----------------------------------
