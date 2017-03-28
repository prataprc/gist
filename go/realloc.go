package main

import "fmt"

func main() {
	a := make([]byte, 0, 1)
	for i := 0; i < 17000; i++ {
		a = append(a, []byte{'a'}...)
		fmt.Printf("i:%v, len:%v, cap:%v\n", i, len(a), cap(a))
	}
}
