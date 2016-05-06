package main

import "fmt"

func main() {
	var c <-chan int
	C := make(chan int, 4)
	c = C

	startsend(C)
	for x := range c {
		fmt.Println("received", x)
	}
	fmt.Println("done")
	close(c)
}

func startsend(c <-chan int) {
	items := [4]int{10, 20, 30, 40}
	for i, x := range items {
		c <- x
	}
}
