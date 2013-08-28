package main

import (
    "fmt"; "unsafe"; "sync/atomic"
)

var x = 10
var m = make( map[string]string )
var keys unsafe.Pointer = unsafe.Pointer(&m)
var y = 20
var s = "hello world"

func main() {
    m["yes"] = "minister"
    m["monty"] = "python"
    fmt.Println(&m, &x, &y, &s)
    fmt.Println(len(m), unsafe.Sizeof(m))

    opp := atomic.LoadPointer(&keys)
    old := (*map[string]string)(opp)
    fmt.Println(&m, keys, opp, old)
}
