package main

import (
	"fmt"
)

func main() {
	var p *int
	a := 0
	defer func() {
		fmt.Println(recover())
	}()
	//fmt.Println(1/a);
	fmt.Println(*p)
	fmt.Println(a)
}
