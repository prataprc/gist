package main

import (
	"flag"
	"fmt"
	"time"
)

func main() {
	flag.Parse()
	what := flag.Args()[0]
	switch what {
	case "slice":
		fmt.Println(sliceAlloc())
	case "alloc":
		fmt.Println(randAlloc())
	}
}

func sliceAlloc() []int64 {
	var sl = []int64{1, 2, 3}
	for {
		sl = append(sl, []int64{3, 2, 1}...)
		sl = sl[3:]
	}
	return sl
}

func randAlloc() [][]byte {
	var sl [][]byte
	count := 1000
	for i := 0; i < 1000000; i++ {
		sl = append(sl, make([]byte, i%count))
	}
	i := 0
	go func() {
		for {
			<-time.After(time.Second)
			fmt.Println(i)
		}
	}()
	for {
		sl = append(sl, make([]byte, i%count))
		sl = sl[1:]
		i++
	}
	return sl
}
