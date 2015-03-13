package main

import "fmt"

type iterator func() int

func main() {
	fn := newiterator()
	for i := 0; i < 10; i++ {
		fmt.Println(fn.read())
	}
}

func newiterator() iterator {
	count := 0
	return func() int {
		count++
		return count
	}
}

func (fn iterator) read() int {
	return fn()
}
