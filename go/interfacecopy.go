package main

import "fmt"

type message struct {
	x, y int
}

func main() {
	ch := make(chan []interface{})
	go sender(ch)
	for x := range ch {
		m := x[0].(message)
		fmt.Printf("%p %p %v\n", &x, &m, m)
	}
}

func sender(ch chan []interface{}) {
	msg := message{10, 20}
	count := 0
	for {
		msg.y = count
		ch <- []interface{}{msg}
		count++
	}
}
