package main

import (
	"fmt"
)

type A struct {
	a int
}

type mapType map[string]interface{}

func (m mapType) mutate(name string, value interface{}) {
	m[name] = value
	fmt.Println("mutated: ", m)
}

func main() {
	m := make(map[int64]A)
	fmt.Println(m[0])
	mi := make(map[string]interface{})
	nodes, ok := mi["nodes"].(string)
	fmt.Println(nodes, ok)

	fmt.Println("test maps are passed by reference in methods receivers")
	another_map := make(mapType)
	fmt.Println("another_map before:", another_map)
	another_map.mutate("this", 10)
	fmt.Println("another_map after:", another_map)

	nilmap(nil)
}

func nilmap(m map[string]interface{}) {
	fmt.Println("looping on nil map")
	for k, v := range m {
		fmt.Println(k, v)
	}
	fmt.Println("Done")
}
