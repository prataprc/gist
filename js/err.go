package main

import (
    "errors"
    "fmt"
)

var egerr = errors.New("closed")

func main() {
    fmt.Println(egerr == egerr)
}
