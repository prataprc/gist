package main

import (
    //"fmt"
)

func main() {
    var sl = []int64{1,2,3}
    for {
        sl = append(sl, []int64{3,2,1}...)
        sl = sl[3:]
        //fmt.Println(sl)
    }
}
