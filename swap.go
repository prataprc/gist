package main

import "fmt"

func main() {
	var x, y = 1, 2
	fmt.Println(x, y)
	y, x = x, y
	fmt.Println(x, y)
}
