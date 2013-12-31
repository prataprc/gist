package main

import (
    "strconv"
    "fmt"
)

func main() {
    fmt.Println(strconv.FormatFloat(-10, 'e', -1, 64))
    fmt.Println(strconv.ParseFloat("-10000000000.0", 64))
}
