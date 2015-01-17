package main

import (
    "flag"
    "time"
)

var options struct {
    n       int // number of parallel go-routines
    maxsize int // Maximum block size to allocate
    loop    int // number allocations
    partial bool
}

func main() {
    flag.IntVar(&options.n, "n", 1, "Number of parallel routines")
    flag.IntVar(&options.maxsize, "maxsize", 1000, "maximum size to allocate")
    flag.IntVar(&options.loop, "loop", 1000000, "number of allocations")
    flag.BoolVar(&options.partial, "partial", false, "demo partial reference")
    flag.Parse()

    if options.partial {
        partialReference()

    } else {
        ch := make(chan bool)
        count := 200000 * 1000 / options.maxsize
        for i := 0; i < options.n; i++ {
            go alloc(options.loop, int64(count), int64(options.maxsize), ch)
        }
        for i := 0; i < options.n; i++ {
            <-ch
        }
    }
}

func alloc(loopcount int, count, maxsize int64, ch chan bool) [][]byte {
    var sl [][]byte
    for i := int64(0); i < count; i++ {
        sl = append(sl, make([]byte, i%maxsize))
    }
    for i := 0; i < loopcount; i++ {
        sl = append(sl, make([]byte, time.Now().UnixNano()%maxsize))
        sl = sl[1:]
    }
    ch <- true
    return sl
}

func partialReference() {
    sl := make([]byte, 0)
    val := make([]byte, 1000)
    for i := 0; i < 10000000; i++ {
        sl = append(sl, val...)
        sl = sl[900:]
    }
}
