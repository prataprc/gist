package main

import "fmt"
import "time"

type X struct {
	a int
	b int
}

func main() {
	ch := make(chan []interface{}, 16)
	go fn(ch)
	item := <-ch
	y := item[0].(X)
	fmt.Printf("main %p\n", &y)
	y.a, y.b = 1000, 2000
}

func fn(ch chan []interface{}) {
	x := X{100, 200}
	fmt.Printf("fn %p\n", &x)
	ch <- []interface{}{x, 10}
	time.Sleep(1 * time.Second)
	fmt.Printf("fn %v\n", x.a, x.b)
}
