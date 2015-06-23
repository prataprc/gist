package main

import "sync"
import "time"
import "log"

var rw sync.Mutex
var some_list = make([]int, 10)

func main() {
    ch := make(chan int, 1000)
    for i := 0; i < 30; i++ {
        some_map := make(map[int][]int)
        for i := 0; i < 10; i++ {
            some_map[i] = some_list
        }
        go routine(i, some_map, ch)
    }
    counts := map[int]int{}
    ncount := 0
    for {
        i := <-ch
        counts[i]++
        ncount++
        if ncount % 10000 == 0 {
            log.Printf("%v\n", ncount)
        }
    }
}

func routine(n int, some_map map[int][]int, ch chan int) {
    for {
        mutex(some_map)
        time.Sleep(1 * time.Millisecond)
        ch<-n
    }
}

func mutex(some_map map[int][]int) {
    //rw.Lock()
    //defer rw.Unlock()
    for i := 0; i < 10; i++ {
        for i := range some_list {
            delete(some_map, i)
            some_map[i] = some_list
        }
    }
}
