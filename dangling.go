package main

import "fmt"

func main() {
    fmt.Println(add())
}

func add() int {
    num := dangling()
    return *num + 1
}

func dangling() *int {
    var i int
    i = 1234
    return &i
}
