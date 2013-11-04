package main

import (
    "fmt"
)

type Node interface {
    prin()
}

func main() {
    m := make(map[int64]Node)
    fmt.Println(m[0] != nil)
}
