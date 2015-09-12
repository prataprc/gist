package main

import "fmt"

func main() {
	recovery := func() {
		fmt.Printf("recovery\n")
		if r := recover(); r != nil {
			fmt.Printf("recovered: %v\n", r)
		}
	}
	func() { defer recovery(); dopanic() }()
}

func dopanic() {
	panic("dopanic")
}
