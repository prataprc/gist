package main

import "fmt"
import "sync/atomic"

type X struct {
    a  chan bool
    b  chan bool
    c  *int64
    d  string
    e uint64
}

func main() {
    s := X{}
    fmt.Println(s.e)
    atomic.AddUint64(&s.e, 1)
    fmt.Println(s.e)
}
