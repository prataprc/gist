package main

import (
    "fmt"
    "time"
)

type X struct {
    i [1000000]int
}

func main() {
    var x X
    var count int
    xp := &x
    y := *xp
    y.i[0] = 10
    fmt.Println(time.Now())
    for i := 0 ; i < 10000; i++ {
        count += fn(*xp).i[0]
    }
    fmt.Println(time.Now(), count)
}

func fn(y X) *X{
    y.i[0] = 10
    return &y
}
