package main

import (
	"flag"
	"strconv"
	"time"
)

func main() {
	flag.Parse()
	count, _ := strconv.Atoi(flag.Args()[0])
	for i := 0; i < count; i++ {
		go randAlloc(1000000, 1000)
	}
	time.Sleep(1000 * time.Second)
}

func randAlloc(count, maxsize int) [][]byte {
	var sl [][]byte
	for i := 0; i < count; i++ {
		sl = append(sl, make([]byte, i%maxsize))
	}
	i := 0
	for {
		sl = append(sl, make([]byte, i%maxsize))
		sl = sl[1:]
		i++
	}
	return sl
}
