package main

import "fmt"

const (
	mutexLocked = 1 << iota // mutex is locked
	mutexWoken
	mutexWaiterShift = iota
)

func main() {
	fmt.Printf("%v %v %v\n", mutexLocked, mutexWoken, mutexWaiterShift)
	new := byte(0xAA)
	new &^= 2
	fmt.Printf("0x%x\n", new)
}
