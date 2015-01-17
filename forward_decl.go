package main

import "fmt"

var fn func(int) int

func main() {
    newFn := wrapFn(fn)
    fn = func(a int) int { return a+1 }
    fmt.Println(newFn(10))
}

func wrapFn(fn func(int)int) func(int) int {
    return func(x int) int {
        y := fn(x)
        return y+1
    }
}
