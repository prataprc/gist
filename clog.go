package main

import (
	"fmt"
	"github.com/couchbaselabs/clog"
)

func main() {
	clog.EnableKey("lmn")
	ch := make(chan byte)
	go routineA(ch)
	go routineB(ch)
	fmt.Println(<-ch)
	fmt.Println(<-ch)
}

func routineA(ch chan byte) {
	clog.EnableKey("xyz")
	fmt.Println("A ...", clog.KeyEnabled("xyz"))
	fmt.Println("A ...", clog.KeyEnabled("abc"))
	ch <- 10
}

func routineB(ch chan byte) {
	clog.EnableKey("abc")
	fmt.Println("B ...", clog.KeyEnabled("xyz"))
	fmt.Println("B ...", clog.KeyEnabled("abc"))
	ch <- 20
}
