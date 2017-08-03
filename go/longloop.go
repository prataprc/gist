package main

import "fmt"

func main() {
	count := 0
	for i := 0; i < 1024*1024*1024; i++ {
		count++
	}
	fmt.Println(count)
}
