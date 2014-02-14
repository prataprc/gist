package main

import (
	"flag"
	"strconv"
)

func main() {
	flag.Parse()
	count, _ := strconv.Atoi(flag.Args()[0])
	ch := make(chan bool)
	for i := 0; i < count; i++ {
		go randAlloc(1000000, 1000, 1000000000, ch)
	}
	for i := 0; i < count; i++ {
		<-ch
	}
}

func randAlloc(count, maxsize, loopcount int, ch chan bool) [][]byte {
	var sl [][]byte
	for i := 0; i < count; i++ {
		sl = append(sl, make([]byte, i%maxsize))
	}
	i := 0
	for i < loopcount {
		sl = append(sl, make([]byte, i%maxsize))
		sl = sl[1:]
		i++
	}
	ch <- true
	return sl
}
