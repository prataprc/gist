package main

import (
    "fmt"
    "unsafe"
    "reflect"
)

func main() {
    var sl []string
    b := (*reflect.SliceHeader)(unsafe.Pointer(&sl))
    fmt.Println("slice header", b, *b)
    fmt.Println(sl, cap(sl))
    sl = append(sl, "hello")
    fmt.Println("slice header", b, *b)
    fmt.Println(sl, cap(sl))
    sl = append(sl, "hello")
    fmt.Println(sl, cap(sl))
    sl = append(sl, "hello")
    fmt.Println(sl, cap(sl))
    sl = append(sl, "hello")
    fmt.Println(sl, cap(sl))
    sl = append(sl, "hello")
    fmt.Println(sl, cap(sl))
}
