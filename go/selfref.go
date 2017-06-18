package main

import (
	"fmt"
)

func main() {
	sl := make([]interface{}, 1)
	sl[0] = sl
	fmt.Println(sl)
}
