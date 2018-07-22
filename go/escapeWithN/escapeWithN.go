package main

import (
    "fmt"
)

var count int

func getIntPtr() *int {
    var res int = count
    count++
    return &res
}

func main() {
    ch := make(chan *int, 100000)
    go dump2Null(ch)
    for i := 0; i < 10000000; i++ {
        v := getIntPtr()
        ch <- v
    }
}

func dump2Null(ch chan *int) {
    for {
        v := <-ch
        fmt.Printf("chan len: %d, vPtr: 0x%X, v:%d\n", len(ch), v, *v)
    }
}
