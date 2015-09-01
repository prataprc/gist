package main

import "strconv"
import "fmt"

func main() {
	x, err := strconv.Atoi("3+")
	fmt.Println(err, x)
}
