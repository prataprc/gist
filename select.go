package main

import (
	"fmt"
)

func main() {
	variant2()
}

func variant1() {
	chone := make(chan bool, 10000)
	for i := 0; i < 10000; i++ {
		chone <- true
	}
	chtwo := make(chan bool, 10000)
	count := 0
	for count < 1000 {
		select {
		case <-chone:
			fmt.Println("chone")
			chtwo <- true
		case <-chtwo:
			fmt.Println("chtwo")
		}
		count++
	}
}

func variant2() {
	chone := make(chan bool, 100)
	chtwo := make(chan bool, 100)
	for i := 0; i < 10000; i++ {
		chone <- true
		chtwo <- true
	}

	var nilch chan bool

	count := 0
	for count < 1000 {
		select {
		case <-chone:
			fmt.Println("chone")
		case <-chtwo:
			fmt.Println("chtwo")
		case <-nilch:
			fmt.Println("reading from nil channel")
		case nilch <- true:
			fmt.Println("writing to channel")
		}
		count++
	}
}
