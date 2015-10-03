package main

import "fmt"

func main() {
	type x struct {
		a int
		b int
	}
	obj := x{10, 20}
	fmt.Println(obj)
}
