package main

import "fmt"

func main() {
    a := []rune("hello world")
    b, c := a[:4], a[4:]
    fmt.Println(a, b, c)
    b = append(b, '0')
    c = append(c, '1')
    fmt.Println(a, b, c)
}
