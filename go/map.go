package main

import (
	"fmt"
)

type A struct {
	a int
}

func main() {
	m := make(map[int64]A)
	fmt.Println(m[0])
	mi := make(map[string]interface{})
	nodes, ok := mi["nodes"].(string)
	fmt.Println(nodes, ok)
}
