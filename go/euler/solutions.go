package main

import "fmt"
import "math"

func p1() {
    sum := 0
    for i := 0; i < 1000; i++ {
        if (i%3) == 0 || (i%5) == 0 {
            sum += i
        }
    }
    fmt.Printf("the sum of all the multiples of 3 or 5 below 1000: %v\n", sum)
}

func p2() {
    till := int64(4 * 1000 * 1000)
    a, b := int64(1), int64(2)
    sum := a
    for b < till {
        sum += b
        a, b = b, a+b
    }
    fmt.Printf(
        "sum of even-valued terms in the fibonacci sequence 1,2...\n"+
            "   whose values do not exceed four million: %v\n", sum)
}

func p3() {
    max := int64(0)
    factors(int64(600851475143), func(n int64) {
        if n > max { max = n }
    })
    fmt.Printf(
        "the largest prime factor of the number 600851475143: %v\n", max)
}

func factors(num int64, fn func(int64)) {
    till := int64(math.Sqrt(float64(num))) + 1
    for i := int64(2); i < till; i++ {
        if num % i == 0 {
            fn(i)
            factors(num / i, fn)
            return
        }
    }
    fn(num)
}
