package main

import "fmt"

func main() {
    var a [10]int
    var b []interface{}
    fmt.Printf("type of a is %v\n", a)
    a = b.(int)
}
