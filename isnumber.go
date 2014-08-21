package main

import "fmt"
import "unicode"

func main() {
    fmt.Println(unicode.IsNumber('0'))
    fmt.Println(unicode.IsNumber('9'))
    fmt.Println(unicode.IsNumber('.'))
    fmt.Println(unicode.IsNumber('a'))
}
