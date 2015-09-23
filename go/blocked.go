package main

import "fmt"

func main() {
	ch := make(chan bool, 2)
	ch <- true
	ch <- true
	fmt.Printf("%d %d\n", len(ch), cap(ch))
}
