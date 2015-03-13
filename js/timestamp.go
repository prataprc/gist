package main

import (
    "log"
    "time"
    "fmt"
)

func main() {
    t := time.Now()
     fmt.Printf("time %v, utc %v\n", t, t.UTC())
    tsold := time.Now().UnixNano()
    for i := 0; i < 10000000000000000; i++ {
        tsnew := time.Now().UnixNano()
        if tsold > tsnew {
            log.Panicln("fail", tsold, tsnew, i)
        }
        tsold = tsnew
    }
}
