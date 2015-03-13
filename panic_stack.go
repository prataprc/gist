package main

import "fmt"
import "strings"
import "runtime/debug"

func main() {
	defer func() {
		recover()
		stackTrace(string(debug.Stack()))
	}()
	fun1()
}

func fun1() {
	fun2()
}

func fun2() {
	panic("error")
}

func stackTrace(s string) {
	for _, line := range strings.Split(s, "\n") {
		fmt.Println("..", line)
	}
}
