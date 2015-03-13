package main

import "fmt"

func main() {
	var sl = make([]interface{}, 10)
	sl[0] = 10
	sl[2] = "string"
	fmt.Printf("%v \n", sl)
}
